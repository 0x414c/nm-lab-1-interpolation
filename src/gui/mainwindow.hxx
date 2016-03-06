#ifndef MAINWINDOW_HXX
#define MAINWINDOW_HXX

#include <functional>

//#include <QtGlobal>

//#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
//#include <QtWidgets/QMainWindow>
//#else
//#include <QtGui/QMainWindow>
//#endif

#include <QColor>
#include <QMainWindow>
#include <QMouseEvent>
#include <QString>
#include <QWheelEvent>
#include <QWidget>

#include "qcustomplot/qcustomplot.h"

#include "../math/functions.hxx"


namespace Ui
{
  class MainWindow;
}


class MainWindow :
  public QMainWindow
{
  Q_OBJECT


  public:
    explicit MainWindow (QWidget* parent = nullptr);

    ~MainWindow (void);


  private slots:
    void on_funcParam_alpha_DoubleSpinBox_valueChanged (double arg1);
    void on_funcParam_beta_DoubleSpinBox_valueChanged (double arg1);
    void on_funcParam_gamma_DoubleSpinBox_valueChanged (double arg1);
    void on_funcParam_delta_DoubleSpinBox_valueChanged (double arg1);
    void on_funcParam_epsilon_DoubleSpinBox_valueChanged (double arg1);
    void on_funcParam_mu_DoubleSpinBox_valueChanged (double arg1);

    void on_plotParam_A_DoubleSpinBox_valueChanged (double arg1);
    void on_plotParam_B_DoubleSpinBox_valueChanged (double arg1);
    void on_plotParam_C_DoubleSpinBox_valueChanged (double arg1);
    void on_plotParam_D_DoubleSpinBox_valueChanged (double arg1);

    void on_interpParam_n_SpinBox_valueChanged (int arg1);
    void on_interpParam_delta_SpinBox_valueChanged (int arg1);

    void on_ctrl_plot_PushButton_clicked (void);
    void on_ctrl_reset_PushButton_clicked (void);
    void on_ctrl_liveUpdate_CheckBox_toggled (bool checked);

    void on_plot_functions_CustomPlot_selectionChangedByUser (void);
    void on_plot_functions_CustomPlot_mousePress (QMouseEvent* ev);
    void on_plot_functions_CustomPlot_mouseWheel (QWheelEvent* ev);
    void on_plot_functions_CustomPlot_mouseMove (QMouseEvent* ev);

    void on_funcList_f_CheckBox_toggled (bool checked);
    void on_funcList_P_n_CheckBox_toggled (bool checked);
    void on_funcList_r_n_CheckBox_toggled (bool checked);
    void on_funcList_d_f_CheckBox_toggled (bool checked);
    void on_funcList_d_P_n_CheckBox_toggled (bool checked);


  private:
    Ui::MainWindow* ui_ = nullptr;

    double wndParam_A_ = 0.;
    double wndParam_B_ = 0.;
    double wndParam_C_ = 0.;
    double wndParam_D_ = 0.;

    double funcParam_alpha_ = 0.;
    double funcParam_beta_ = 0.;
    double funcParam_gamma_ = 0.;
    double funcParam_delta_ = 0.;
    double funcParam_epsilon_ = 0.;
    double funcParam_mu_ = 0.;

    int interpParam_n_ = 2;
    double interpParam_delta_ = 0.;

    bool liveUpdateEnabled_ = false;
    bool isDirty_ = false;

    double prop_x_0_ = 0.;
    double prop_delta_ = 0.;

    Math::FunctionType functionType_ = Math::FunctionType::_;

    void enableFunctionType (
      Math::FunctionType functionType, bool enabled = true
    );
    bool isFunctionTypeEnabled (
      Math::FunctionType functionType, bool enabled = true
    );

    void initSignalsAndSlots (void);
    void setDefaults (void);

    void setDirty (bool isDirty = true);

    void initCustomPlot (QCustomPlot* const customPlot);
    void enableCustomPlot (QCustomPlot* const customPlot, bool enabled = true);
    void clearCustomPlot (QCustomPlot* const customPlot);
    void updateCustomPlot (QCustomPlot* const customPlot);

    void plotFunction (
      const std::function<double (double)>& f, int samplesCount,
      double keyStart, double keyEnd, double valueStart, double valueEnd,
      const QColor& color, QCustomPlot* const customPlot, const QString& name
    );

    void plotPolynomial (
      const std::function<double (double)>& f, int samplesCount, int stepsCount,
      double keyStart, double keyEnd, double valueStart, double valueEnd,
      const QColor& color, QCustomPlot* const customPlot, const QString& name
    );

    void plotBoundingBox (
      double keyStart, double keyEnd, double valueStart, double valueEnd,
      const QColor& color, QCustomPlot* const customPlot
    );

    void plotMax (
      const std::function<double (double)>& func, int samplesCount,
      double keyStart, double keyEnd,
      const QColor& color, QCustomPlot* const customPlot
    );
};


#endif // MAINWINDOW_HXX
