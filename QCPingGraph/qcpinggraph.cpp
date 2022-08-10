#include "qcpinggraph.h"

QCPingGraph::QCPingGraph(QWidget *parent) : QWidget(parent)
{
    widgetPingGraph = new QCustomPlot(this);
    widgetPingGraph->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *mainLayout = new QVBoxLayout;

    setLayout(mainLayout);

    mainLayout->addWidget(widgetPingGraph);
    setup(widgetPingGraph);

    widgetPingGraph->replot();

    pQCPing = new QCPing();
    connect(pQCPing, SIGNAL(sigGetResponseTime(qlonglong)), this, SLOT(slotGetResponseTime(qlonglong)));
}

void QCPingGraph::setup(QCustomPlot *w)
{
    w->addGraph(); // blue line
    w->graph(0)->setPen(QPen(QColor(40, 110, 255)));

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    w->xAxis->setTicker(timeTicker);
    w->axisRect()->setupFullAxesBox();
    w->yAxis->setRange(-1.0, 1000.0);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(w->xAxis, SIGNAL(rangeChanged(QCPRange)), w->xAxis2, SLOT(setRange(QCPRange)));
    connect(w->yAxis, SIGNAL(rangeChanged(QCPRange)), w->yAxis2, SLOT(setRange(QCPRange)));
}

int QCPingGraph::ping(bool bStart)
{
    if (nullptr != pQCPing) {
        return pQCPing->ping(bStart);
    }

    return -1;
}

void QCPingGraph::setIP(QString ip)
{
    if (nullptr != pQCPing) {
        pQCPing->setIP(ip);
    }
}

void QCPingGraph::slotGetResponseTime(qlonglong us)
{
    QDateTime currTime = QDateTime::currentDateTime();

    qDebug() << "time : " << us;
#if 0
    if (us >= 0) {
        ui->editPingTimeRecord->textCursor().insertText("[" + currTime.toString("yyyy-MM-ddT hh:mm:ss") +
                                                    "] " + QString::number(us) + "us\n");
    }
    else {
        ui->editPingTimeRecord->textCursor().insertText("[" + currTime.toString("yyyy-MM-ddT hh:mm:ss") +
                                                    "] timeout\n");
    }
#endif

    static QTime timeStart = QTime::currentTime();
    // calculate two new data points:
    double key = timeStart.msecsTo(QTime::currentTime())/1000.0; // time elapsed since start of demo, in seconds
    static double lastPointKey = 0;
    if (key-lastPointKey > 0.002) // at most add point every 2 ms
    {
      // add data to lines:
      widgetPingGraph->graph(0)->addData(key, us/1000.);
      lastPointKey = key;
    }
    // make key axis range scroll with the data (at a constant range size of 8):
    widgetPingGraph->xAxis->setRange(key, 8, Qt::AlignRight);
    widgetPingGraph->replot();
}
