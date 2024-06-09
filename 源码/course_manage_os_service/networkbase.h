#ifndef NETWORKBASE_H
#define NETWORKBASE_H

#include <iostream>
#include <QFileInfo>
#include <QObject>
#include <QTimer>
#include <QTcpServer>
#include <QTcpSocket>

#include "ConnectStatus.h"

class NetWorkBase : public QObject
{
    Q_OBJECT
public:
    explicit NetWorkBase(QObject *parent = nullptr);

private:
    // 监听
    QTcpServer* tcp_server_;
    // tcp套接字
    QTcpSocket* tcp_socket_;
    // 现在的状况
    ConnectStatus now_;
    // 是不是头
    bool ishead_ = true;
    // 文件
    QFile    file_;
    int 	 file_size_ = 0;
    // 定时器防止粘包
    QTimer   timer_;

    // 设置新链接
    void setNewSocket();
    // 准备读取
    void readyRead();
    // 更新文件
    void updateFile(const QByteArray& data);
    // 传送文件
    void passFile();

signals:

};

#endif // NETWORKBASE_H
