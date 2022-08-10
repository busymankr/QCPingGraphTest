#ifndef QCPINGGRAPH_H
#define QCPINGGRAPH_H

#include <QWidget>
#include "qcping.h"
#include "qcustomplot.h"

class QCPingGraph : public QWidget
{
    Q_OBJECT
public:
    explicit QCPingGraph(QWidget *parent = nullptr);

    /**
     * @brief ping
     * @param bStart
     * @return
     */
    int ping(bool bStart);

    /**
     * @brief setIP
     * @param ip
     */
    void setIP(QString ip);

private:
    /**
     * @brief setup
     * @param w
     */
    void setup(QCustomPlot *w);

signals:

private slots:
    void slotGetResponseTime(qlonglong us);

private:
    QCPing *pQCPing;
    QCustomPlot *widgetPingGraph;
};

#endif // QCPINGGRAPH_H
