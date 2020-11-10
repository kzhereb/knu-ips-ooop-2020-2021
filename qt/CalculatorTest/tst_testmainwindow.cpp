#include <QtTest>
#include <QCoreApplication>
#include <QLabel>

// add necessary includes here
#include "../Calculator/mainwindow.h"

class TestMainWindow : public QObject
{
    Q_OBJECT

public:
    TestMainWindow();
    ~TestMainWindow();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_numberClicked();

};

TestMainWindow::TestMainWindow()
{

}

TestMainWindow::~TestMainWindow()
{

}

void TestMainWindow::initTestCase()
{

}

void TestMainWindow::cleanupTestCase()
{

}

void TestMainWindow::test_numberClicked()
{
    MainWindow* window = new MainWindow();
    QTest::keyClick(window, '1');
    QCOMPARE(window->findChild<QLabel*>("lbl_Result")->text(), "1");
}

QTEST_MAIN(TestMainWindow)

#include "tst_testmainwindow.moc"
