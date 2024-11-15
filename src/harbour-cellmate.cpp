#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <sailfishapp.h>
#include <QtQml>
#include <CellWatcher.h>
#include <ltecellwatcher.h>
#include <umtscellwatcher.h>
#include <servingcellwatcher.h>
#include <gsmcellwatcher.h>
#include <locationprovider.h>
#include <logrecorder.h>

int main(int argc, char *argv[])
{
    // SailfishApp::main() will display "qml/harbour-cellmate.qml", if you need more
    // control over initialization, you can use:
    //
    //   - SailfishApp::application(int, char *[]) to get the QGuiApplication *
    //   - SailfishApp::createView() to get a new QQuickView * instance
    //   - SailfishApp::pathTo(QString) to get a QUrl to a resource file
    //   - SailfishApp::pathToMainQml() to get a QUrl to the main QML file
    //
    // To display the view, call "show()" (will show fullscreen on device).

    QScopedPointer<QGuiApplication> app(SailfishApp::application(argc, argv));
    QScopedPointer<QQuickView> v(SailfishApp::createView());

    qmlRegisterType<CellWatcher>("co.uk.solotel", 1, 0, "CellWatcher");
    CellWatcher* cellWatcher = new CellWatcher();

    LTECellWatcher* lteSignals = new LTECellWatcher(cellWatcher);
    UMTSCellWatcher* umtsSignals = new UMTSCellWatcher(cellWatcher);
    GSMCellWatcher* gsmSignals = new GSMCellWatcher(cellWatcher);

    ServingCellWatcher* servingWatcher = new ServingCellWatcher(cellWatcher);

    QSortFilterProxyModel *lte_sorted_signals = new QSortFilterProxyModel();
    lte_sorted_signals->setSourceModel(lteSignals);
    lte_sorted_signals->setSortRole(LTECellWatcher::RSRPRole);
    lte_sorted_signals->sort(0, Qt::AscendingOrder);

    QSortFilterProxyModel *umts_sorted_signals = new QSortFilterProxyModel();
    umts_sorted_signals->setSourceModel(umtsSignals);
    umts_sorted_signals->setSortRole(UMTSCellWatcher::SignalStrengthRole);
    umts_sorted_signals->sort(0, Qt::DescendingOrder);

    QSortFilterProxyModel *gsm_sorted_signals = new QSortFilterProxyModel();
    gsm_sorted_signals->setSourceModel(gsmSignals);
    gsm_sorted_signals->setSortRole(GSMCellWatcher::SignalStrengthRole);
    gsm_sorted_signals->sort(0, Qt::DescendingOrder);

    LocationProvider* locationProvider = new LocationProvider();

    LogRecorder* logRecorder = new LogRecorder(cellWatcher, locationProvider);

    v->rootContext()->setContextProperty("location", locationProvider);
    v->rootContext()->setContextProperty("lteSignals", lte_sorted_signals);
    v->rootContext()->setContextProperty("umtsSignals", umts_sorted_signals);
    v->rootContext()->setContextProperty("gsmSignals", gsm_sorted_signals);
    v->rootContext()->setContextProperty("serving", servingWatcher);
    v->rootContext()->setContextProperty("logger", logRecorder);

    v->setSource(SailfishApp::pathTo("qml/harbour-cellmate.qml"));
    v->show();

    return app->exec();
}
