#include "networkbase.h"

NetWorkBase::NetWorkBase(QObject *parent)
    : QObject{parent},
      // 绑定在对象树上，防止内存泄漏
      tcp_server_(new QTcpServer(this)),
      tcp_socket_(nullptr),
      now_(normal)
{
    tcp_server_->listen(QHostAddress::Any, 8889);

    connect(tcp_server_, &QTcpServer::newConnection, this, &NetWorkBase::setNewSocket);
    connect(&timer_, &QTimer::timeout, this, &NetWorkBase::passFile);
}

void NetWorkBase::setNewSocket()
{
    tcp_socket_ = tcp_server_->nextPendingConnection();
    QString info = "ip :  " + tcp_socket_->peerAddress().toString() + "\n"
            + "port:  " + QString::number(tcp_socket_->peerPort());

    std::cout << info.toStdString() << '\n';
    connect(tcp_socket_, &QTcpSocket::readyRead, this, &NetWorkBase::readyRead);
}

void NetWorkBase::readyRead()
{
    auto data = tcp_socket_->readAll();
    QString data_str = data_str.fromLocal8Bit(data);

    switch(this->now_)
    {
    case normal:
        // 判断传输的状况并且改变状态
        if (data_str == "up")
            now_ = up;
        else if (data_str == "down")
            now_  = down;
        else
            now_ = normal;
        break;

    case up:
        if (ishead_)
        {
            // 打开文件
            auto file_name= data_str.section("##", 0, 0);
            file_size_  = data_str.section("##", 1, 1).toInt();
            file_.setFileName(file_name);
            ishead_ = false;
        }
        else
        {
            updateFile(data);
            ishead_ = true;
            now_ = normal;
        }
        break;
    case down:
        QFileInfo file_info(data_str);
        if (!file_info.exists())
         {
                std::cout << "open file fail" << '\n';
                tcp_socket_->disconnectFromHost();
                tcp_socket_->close();
                now_ = normal;
        }
        else
        {
                QString file_head = QString("%1##%2").arg(file_info.fileName()).arg(file_info.size());
                file_size_ = file_info.size();
                file_.setFileName(data_str);
                // 写入文件头
                tcp_socket_->write(file_head.toStdString().c_str());
                // 启动定时器防止粘包(20)ms
                timer_.start(20);
                now_ = normal;
        }
        break;
    }
}

void NetWorkBase::updateFile(const QByteArray& data)
{
    int  write_len = 0;
    if (!file_.open(QIODevice::WriteOnly))
    {
        std::cout << "open file fail" << '\n';
        tcp_socket_->disconnectFromHost();
        tcp_socket_->close();
        now_ = normal;
        // 清空数据区
        return ;
    }
    else
    {
        write_len = file_.write(data);
        file_.close();
        // 传输状态之后关闭
        if (write_len == file_size_)
            std::cout << "Succeed" << '\n';

        tcp_socket_->disconnectFromHost();
        tcp_socket_->close();
    }
}

void NetWorkBase::passFile()
{
    if (!file_.open(QIODevice::ReadOnly))
    {
        std::cout << "open file fail" << '\n';
        tcp_socket_->disconnectFromHost();
        tcp_socket_->close();
        now_ = normal;
        timer_.stop();
        // 发送状态
        return ;
    }
    else
    {
        auto data = file_.readAll();
        auto write_len= tcp_socket_->write(data);

        if (write_len == file_size_)
            std::cout << "succeed" << '\n';
        else
            std::cout << "fail" << '\n';

        file_.close();
        tcp_socket_->disconnectFromHost();
        tcp_socket_->close();
        now_ = normal;
        timer_.stop();
    }
}
