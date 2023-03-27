#include <QtTest>
#include <QCoreApplication>
#include <QLabel>
#include <QPushButton>
#include <QListView>

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
    QTest::mouseClick(window->findChild<QPushButton*>("btnPlus"), Qt::LeftButton);
    QCOMPARE(window->findChild<QLabel*>("lbl_Result")->text(), "1+");
    QTest::keyClick(window, '2');
    QCOMPARE(window->findChild<QLabel*>("lbl_Result")->text(), "1+2");
    QListView* history = window->findChild<QListView*>("lsvHistory");
    QCOMPARE(history->model()->rowCount(),0);

    QTest::mouseClick(window->findChild<QPushButton*>("btnEquals"), Qt::LeftButton);
    QCOMPARE(window->findChild<QLabel*>("lbl_Result")->text(), "3");
    QCOMPARE(history->model()->rowCount(),1);
    QCOMPARE(history->model()->data(history->model()->index(0,0)).toString(),"1 + 2 = 3");

}

QTEST_MAIN(TestMainWindow)

#include "tst_testmainwindow.moc"
