#include <cmath>
#include <cstddef>

#include <algorithm>
#include <functional>
#include <limits>

#include <QBrush>
#include <QColor>
#include <QLocale>
#include <QMainWindow>
#include <QMouseEvent>
#include <QPen>
#include <QString>
#include <QVector>
#include <QWheelEvent>
#include <QWidget>

#include "qcustomplot/qcustomplot.h"

#include "ui_mainwindow.h"

#include "mainwindow.hxx"
#include "../config.hxx"
#include "../math/functions.hxx"
#include "../math/mathutils.hxx"
#include "../math/newtonpolynomial.hxx"
#include "../math/numerictypes.hxx"


#pragma region init/destroy

MainWindow::MainWindow (QWidget* parent) :
  QMainWindow (parent),
  ui_ (new Ui::MainWindow)
{
  ui_->setupUi (this);
//  initSignalsAndSlots ();
  setDefaults ();
  initCustomPlot (ui_->plot_functions_CustomPlot);
}


MainWindow::~MainWindow (void)
{
  delete ui_;
}

#pragma endregion // init/destroy


#pragma region private slots

void
MainWindow::on_funcParam_alpha_DoubleSpinBox_valueChanged (double arg1)
{
  funcParam_alpha_ = arg1;

  qDebug () << "funcParam_alpha_ ==" << funcParam_alpha_;

  setDirty (true);
}


void
MainWindow::on_funcParam_beta_DoubleSpinBox_valueChanged (double arg1)
{
  funcParam_beta_ = arg1;

  qDebug () << "funcParam_beta_ ==" << funcParam_beta_;

  setDirty (true);
}


void
MainWindow::on_funcParam_gamma_DoubleSpinBox_valueChanged (double arg1)
{
  funcParam_gamma_ = arg1;

  qDebug () << "funcParam_gamma_ ==" << funcParam_gamma_;

  setDirty (true);
}


void
MainWindow::on_funcParam_delta_DoubleSpinBox_valueChanged (double arg1)
{
  funcParam_delta_ = arg1;

  qDebug () << "funcParam_delta_ ==" << funcParam_delta_;

  setDirty (true);
}


void
MainWindow::on_funcParam_epsilon_DoubleSpinBox_valueChanged (double arg1)
{
  funcParam_epsilon_ = arg1;

  qDebug () << "funcParam_epsilon_ ==" << funcParam_epsilon_;

  setDirty (true);
}


void
MainWindow::on_funcParam_mu_DoubleSpinBox_valueChanged (double arg1)
{
  funcParam_mu_ = arg1;

  qDebug () << "funcParam_mu_ ==" << funcParam_mu_;

  setDirty (true);
}


void
MainWindow::on_plotParam_A_DoubleSpinBox_valueChanged (double arg1)
{
  using namespace Config::GUI::InputLimits;


  if (arg1 >= ABCD_Min && arg1 <= ABCD_Max)
  {
    if (arg1 >= ui_->plotParam_B_DoubleSpinBox->value ())
    {
      ui_->plotParam_B_DoubleSpinBox->setValue (arg1);
    }

    wndParam_A_ = arg1;

    qDebug () << "wndParam_A_ ==" << wndParam_A_;

    setDirty (true);
  }
}


void
MainWindow::on_plotParam_B_DoubleSpinBox_valueChanged (double arg1)
{
  using namespace Config::GUI::InputLimits;


  if (arg1 >= ABCD_Min && arg1 <= ABCD_Max)
  {
    if (arg1 <= ui_->plotParam_A_DoubleSpinBox->value ())
    {
      ui_->plotParam_A_DoubleSpinBox->setValue (arg1);
    }

    wndParam_B_ = arg1;

    qDebug () << "wndParam_B_ ==" << wndParam_B_;

    setDirty (true);
  }
}


void
MainWindow::on_plotParam_C_DoubleSpinBox_valueChanged (double arg1)
{
  using namespace Config::GUI::InputLimits;


  if (arg1 >= ABCD_Min && arg1 <= ABCD_Max)
  {
    if (arg1 >= ui_->plotParam_D_DoubleSpinBox->value ())
    {
      ui_->plotParam_D_DoubleSpinBox->setValue (arg1);
    }

    wndParam_C_ = arg1;

    qDebug () << "wndParam_C_ ==" << wndParam_C_;

    setDirty (true);
  }
}


void
MainWindow::on_plotParam_D_DoubleSpinBox_valueChanged (double arg1)
{
  using namespace Config::GUI::InputLimits;


  if (arg1 >= ABCD_Min && arg1 <= ABCD_Max)
  {
    if (arg1 <= ui_->plotParam_C_DoubleSpinBox->value ())
    {
      ui_->plotParam_C_DoubleSpinBox->setValue (arg1);
    }

    wndParam_D_ = arg1;

    qDebug () << "wndParam_D_ ==" << wndParam_D_;

    setDirty (true);
  }
}


void
MainWindow::on_interpParam_n_SpinBox_valueChanged (int arg1)
{
  interpParam_n_ = arg1;

  qDebug () << "interpParam_n_ ==" << interpParam_n_;

  setDirty (true);
}


void
MainWindow::on_interpParam_delta_SpinBox_valueChanged (int arg1)
{
  interpParam_delta_ = std::pow (10., double (arg1));

  qDebug () << "interpParam_delta_ ==" << interpParam_delta_;

  setDirty (true);
}


void
MainWindow::on_ctrl_plot_PushButton_clicked (void)
{
  qDebug() << "on_ctrl_plot_PushButton_clicked";

  updateCustomPlot (ui_->plot_functions_CustomPlot);
}


void
MainWindow::on_ctrl_reset_PushButton_clicked (void)
{
  qDebug() << "on_ctrl_reset_PushButton_clicked";

  clearCustomPlot (ui_->plot_functions_CustomPlot);
}


void
MainWindow::on_ctrl_liveUpdate_CheckBox_toggled (bool checked)
{
  liveUpdateEnabled_ = checked;

  qDebug () << "liveUpdateEnabled_ ==" << liveUpdateEnabled_;

  setDirty (true);
}


void
MainWindow::on_plot_functions_CustomPlot_selectionChangedByUser (void)
{
  QCustomPlot* const customPlot (qobject_cast<QCustomPlot*> (sender ()));

  if (
    customPlot->xAxis->selectedParts ().testFlag (QCPAxis::spAxis) ||
    customPlot->xAxis->selectedParts ().testFlag (QCPAxis::spTickLabels) ||
    customPlot->xAxis2->selectedParts ().testFlag (QCPAxis::spAxis) ||
    customPlot->xAxis2->selectedParts ().testFlag (QCPAxis::spTickLabels)
  )
  {
    customPlot->xAxis2->setSelectedParts (
      QCPAxis::spAxis | QCPAxis::spTickLabels
    );
    customPlot->xAxis->setSelectedParts (
      QCPAxis::spAxis | QCPAxis::spTickLabels
    );
  }

  if (
    customPlot->yAxis->selectedParts ().testFlag (QCPAxis::spAxis) ||
    customPlot->yAxis->selectedParts ().testFlag (QCPAxis::spTickLabels) ||
    customPlot->yAxis2->selectedParts ().testFlag (QCPAxis::spAxis) ||
    customPlot->yAxis2->selectedParts ().testFlag (QCPAxis::spTickLabels)
  )
  {
    customPlot->yAxis2->setSelectedParts (
      QCPAxis::spAxis | QCPAxis::spTickLabels
    );
    customPlot->yAxis->setSelectedParts (
      QCPAxis::spAxis | QCPAxis::spTickLabels
    );
  }

  for (int i (0); i < customPlot->plottableCount (); ++i)
  {
    QCPAbstractPlottable* const plottable (customPlot->plottable (i));
    QCPPlottableLegendItem* const item (
      customPlot->legend->itemWithPlottable (plottable)
    );

    if (item->selected () || plottable->selected ())
    {
      item->setSelected (true);
      plottable->setSelected (true);
    }
  }
}


void
MainWindow::on_plot_functions_CustomPlot_mousePress (QMouseEvent* ev)
{
  QCustomPlot* const customPlot (qobject_cast<QCustomPlot*> (sender ()));

  if (
    customPlot->xAxis->selectedParts ().testFlag (QCPAxis::spAxis)
  )
  {
    customPlot->axisRect ()->setRangeDrag (customPlot->xAxis->orientation ());
  }
  else
  {
    if (
      customPlot->yAxis->selectedParts ().testFlag (QCPAxis::spAxis)
    )
    {
      customPlot->axisRect ()->setRangeDrag (customPlot->yAxis->orientation ());
    }
    else
    {
      customPlot->axisRect ()->setRangeDrag (Qt::Horizontal | Qt::Vertical);
    }
  }
}


void
MainWindow::on_plot_functions_CustomPlot_mouseWheel (QWheelEvent* ev)
{
  QCustomPlot* const customPlot (qobject_cast<QCustomPlot*> (sender ()));

  if (
    customPlot->xAxis->selectedParts ().testFlag (QCPAxis::spAxis)
  )
  {
    customPlot->axisRect ()->setRangeZoom (customPlot->xAxis->orientation ());
  }
  else
  {
    if (
      customPlot->yAxis->selectedParts ().testFlag (QCPAxis::spAxis))
    {
      customPlot->axisRect ()->setRangeZoom (customPlot->yAxis->orientation ());
    }
    else
    {
      customPlot->axisRect ()->setRangeZoom (Qt::Horizontal | Qt::Vertical);
    }
  }
}


void
MainWindow::on_plot_functions_CustomPlot_mouseMove (QMouseEvent* ev)
{
  QCustomPlot* const customPlot (qobject_cast<QCustomPlot*> (sender ()));

  const double x (customPlot->xAxis->pixelToCoord (ev->pos ().x ()));
  const double y (customPlot->yAxis->pixelToCoord (ev->pos ().y ()));

  customPlot->setToolTip (QString ("(%1; %2)").arg (x).arg (y));
}


void
MainWindow::on_funcList_f_CheckBox_toggled (bool checked)
{
  enableFunctionType (Math::FunctionType::f, checked);

  setDirty (true);
}


void
MainWindow::on_funcList_P_n_CheckBox_toggled (bool checked)
{
  enableFunctionType (Math::FunctionType::P_n, checked);

  setDirty (true);
}


void
MainWindow::on_funcList_r_n_CheckBox_toggled (bool checked)
{
  enableFunctionType (Math::FunctionType::r_n, checked);

  setDirty (true);
}


void
MainWindow::on_funcList_d_f_CheckBox_toggled (bool checked)
{
  enableFunctionType (Math::FunctionType::d_f, checked);

  setDirty (true);
}


void
MainWindow::on_funcList_d_P_n_CheckBox_toggled (bool checked)
{
  enableFunctionType (Math::FunctionType::d_P_n, checked);

  setDirty (true);
}

#pragma endregion // private slots


#pragma region private methods

void
MainWindow::enableFunctionType (Math::FunctionType functionType, bool enabled)
{
  if (enabled)
  {
    functionType_ = Math::FunctionType (
      int (functionType_) | int (functionType)
    );
  }
  else
  {
    functionType_ = Math::FunctionType (
      int (functionType_) & ~(int (functionType))
    );
  }

  qDebug () << "functionType_ ==" << int (functionType_);
}


bool
MainWindow::isFunctionTypeEnabled (
  Math::FunctionType functionType, bool enabled
)
{
  return (
    ((int (functionType_) & int (functionType)) == int (functionType))
    == enabled
  );
}


[[deprecated("This is a workaround for strange autoconnection issues.")]]
void
MainWindow::initSignalsAndSlots (void)
{
//  connect (
//    ui_->plotParam_A_DoubleSpinBox, &QDoubleSpinBox::valueChanged,
//    this, &MainWindow::on_plotParam_A_DoubleSpinBox_valueChanged
//  );

  connect (
    ui_->funcParam_alpha_DoubleSpinBox, SIGNAL (valueChanged (double)),
    this, SLOT (on_funcParam_alpha_DoubleSpinBox_valueChanged (double))
  );

  connect (
    ui_->funcParam_beta_DoubleSpinBox, SIGNAL (valueChanged (double)),
    this, SLOT (on_funcParam_beta_DoubleSpinBox_valueChanged (double))
  );

  connect (
    ui_->funcParam_gamma_DoubleSpinBox, SIGNAL (valueChanged (double)),
    this, SLOT (on_funcParam_gamma_DoubleSpinBox_valueChanged (double))
  );

  connect (
    ui_->funcParam_delta_DoubleSpinBox, SIGNAL (valueChanged (double)),
    this, SLOT (on_funcParam_delta_DoubleSpinBox_valueChanged (double))
  );

  connect (
    ui_->funcParam_epsilon_DoubleSpinBox, SIGNAL (valueChanged (double)),
    this, SLOT (on_funcParam_epsilon_DoubleSpinBox_valueChanged (double))
  );

  connect (
    ui_->funcParam_mu_DoubleSpinBox, SIGNAL (valueChanged (double)),
    this, SLOT (on_funcParam_mu_DoubleSpinBox_valueChanged (double))
  );


  connect (
    ui_->plotParam_A_DoubleSpinBox, SIGNAL (valueChanged (double)),
    this, SLOT (on_plotParam_A_DoubleSpinBox_valueChanged (double))
  );

  connect (
    ui_->plotParam_B_DoubleSpinBox, SIGNAL (valueChanged (double)),
    this, SLOT (on_plotParam_B_DoubleSpinBox_valueChanged (double))
  );

  connect (
    ui_->plotParam_C_DoubleSpinBox, SIGNAL (valueChanged (double)),
    this, SLOT (on_plotParam_C_DoubleSpinBox_valueChanged (double))
  );

  connect (
    ui_->plotParam_D_DoubleSpinBox, SIGNAL (valueChanged (double)),
    this, SLOT (on_plotParam_D_DoubleSpinBox_valueChanged (double))
  );


  connect (
    ui_->interpParam_n_SpinBox, SIGNAL (valueChanged (int)),
    this, SLOT (on_interpParam_n_SpinBox_valueChanged (int))
  );

  connect (
    ui_->interpParam_delta_SpinBox, SIGNAL (valueChanged (int)),
    this, SLOT (on_interpParam_delta_SpinBox_valueChanged (int))
  );


  connect (
    ui_->ctrl_plot_PushButton, SIGNAL (clicked (void)),
    this, SLOT (on_ctrl_plot_PushButton_clicked (void))
  );

  connect (
    ui_->ctrl_reset_PushButton, SIGNAL (clicked (void)),
    this, SLOT (on_ctrl_reset_PushButton_clicked (void))
  );

  connect (
    ui_->ctrl_liveUpdate_CheckBox, SIGNAL (toggled (bool)),
    this, SLOT (on_ctrl_liveUpdate_CheckBox_toggled (bool))
  );


  connect (
    ui_->funcList_f_CheckBox, SIGNAL (toggled (bool)),
    this, SLOT (on_funcList_f_CheckBox_toggled (bool))
  );

  connect (
    ui_->funcList_P_n_CheckBox, SIGNAL (toggled (bool)),
    this, SLOT (on_funcList_P_n_CheckBox_toggled (bool))
  );

  connect (
    ui_->funcList_r_n_CheckBox, SIGNAL (toggled (bool)),
    this, SLOT (on_funcList_r_n_CheckBox_toggled (bool))
  );

  connect (
    ui_->funcList_d_f_CheckBox, SIGNAL (toggled (bool)),
    this, SLOT (on_funcList_d_f_CheckBox_toggled (bool))
  );

  connect (
    ui_->funcList_d_P_n_CheckBox, SIGNAL (toggled (bool)),
    this, SLOT (on_funcList_d_P_n_CheckBox_toggled (bool))
  );
}


void
MainWindow::setDefaults (void)
{
  using namespace Config::GUI::Defaults;


  ui_->funcParam_alpha_DoubleSpinBox->setValue (Alpha);
  ui_->funcParam_beta_DoubleSpinBox->setValue (Beta);
  ui_->funcParam_gamma_DoubleSpinBox->setValue (Gamma);
  ui_->funcParam_delta_DoubleSpinBox->setValue (Delta);
  ui_->funcParam_epsilon_DoubleSpinBox->setValue (Epsilon);
  ui_->funcParam_mu_DoubleSpinBox->setValue (Mu);

  ui_->plotParam_A_DoubleSpinBox->setValue (A);
  ui_->plotParam_B_DoubleSpinBox->setValue (B);
  ui_->plotParam_C_DoubleSpinBox->setValue (C);
  ui_->plotParam_D_DoubleSpinBox->setValue (D);

  ui_->interpParam_n_SpinBox->setValue (N);
  ui_->interpParam_delta_SpinBox->setValue (DeltaExponent);

  ui_->funcList_f_CheckBox->setChecked (true);
  ui_->funcList_P_n_CheckBox->setChecked (true);
//  ui_->funcList_r_n_CheckBox->setChecked (true);
//  ui_->funcList_d_f_CheckBox->setChecked (true);
//  ui_->funcList_d_P_n_CheckBox->setChecked (true);

  ui_->ctrl_liveUpdate_CheckBox->setChecked (LiveUpdateEnabled);
}


void
MainWindow::setDirty (bool isDirty)
{
  isDirty_ = isDirty;

  qDebug () << "isDirty_ ==" << isDirty_;

  if (isDirty_ && liveUpdateEnabled_)
  {
    // TODO: [~~] Update only parts of the plot that were modified.
    updateCustomPlot (ui_->plot_functions_CustomPlot);
  }
}


void
MainWindow::initCustomPlot (QCustomPlot* customPlot)
{
  using namespace Config::GUI::PlotParams;


  const QFont normalFont (font ().family (), FontSize);
  const QFont boldFont (font ().family (), FontSize, QFont::Bold);

  customPlot->setInteractions (
    QCP::iRangeDrag | QCP::iRangeZoom |
    QCP::iSelectPlottables | QCP::iSelectAxes |
    QCP::iSelectLegend | QCP::iSelectItems
  );

  customPlot->setLocale (
    QLocale (QLocale::English, QLocale::UnitedStates)
  );

//  customPlot->setNoAntialiasingOnDrag (true);
//  customPlot->setNotAntialiasedElements (QCP::aeAll);
  customPlot->setAntialiasedElements (QCP::aeAll);

//  customPlot->plotLayout ()->insertRow (0);
//  customPlot->plotLayout ()->addElement (0, 0, new QCPPlotTitle (customPlot, "Plot (1)."));

  customPlot->legend->setVisible (true);
  customPlot->legend->setFont (normalFont);
  customPlot->legend->setSelectedFont (boldFont);
  customPlot->legend->setSelectableParts (QCPLegend::spItems);

  customPlot->setAutoAddPlottableToLegend (true);

  customPlot->setBackgroundScaled (true);
  customPlot->setBackgroundScaledMode (Qt::IgnoreAspectRatio);

//  customPlot->axisRect ()->setupFullAxesBox (true);
  customPlot->xAxis2->setVisible (true);
  customPlot->xAxis2->setTickLabels (false);

  customPlot->yAxis2->setVisible (true);
  customPlot->yAxis2->setTickLabels (false);

  customPlot->xAxis->setSelectableParts (
    QCPAxis::spAxis | QCPAxis::spTickLabels
  );

  customPlot->yAxis->setSelectableParts (
    QCPAxis::spAxis | QCPAxis::spTickLabels
  );

  customPlot->xAxis->setRange (-1., 1.);
  customPlot->yAxis->setRange (-1., 1.);

  customPlot->xAxis->setLabel (QStringLiteral ("x"));
  customPlot->yAxis->setLabel (QStringLiteral ("y"));

  connect (
    customPlot, SIGNAL (selectionChangedByUser (void)),
    this, SLOT (on_plot_functions_CustomPlot_selectionChangedByUser (void))
  );

  connect (
    customPlot, SIGNAL (mousePress (QMouseEvent*)),
    this, SLOT (on_plot_functions_CustomPlot_mousePress (QMouseEvent*))
  );

  connect (
    customPlot, SIGNAL (mouseWheel (QWheelEvent*)),
    this, SLOT (on_plot_functions_CustomPlot_mouseWheel (QWheelEvent*))
  );

  connect (
    customPlot->xAxis, SIGNAL (rangeChanged (QCPRange)),
    customPlot->xAxis2, SLOT (setRange (QCPRange))
  );

  connect (
    customPlot->yAxis, SIGNAL (rangeChanged (QCPRange)),
    customPlot->yAxis2, SLOT (setRange (QCPRange))
  );

  connect (
    customPlot, SIGNAL (mouseMove (QMouseEvent*)),
    this, SLOT (on_plot_functions_CustomPlot_mouseMove (QMouseEvent*))
  );
}


void
MainWindow::enableCustomPlot (QCustomPlot* customPlot, bool enabled)
{
  if (enabled)
  {
    customPlot->setBackground (Qt::white);
  }
  else
  {
    customPlot->setBackground (Qt::lightGray);
  }

  customPlot->setEnabled (enabled);
}


void
MainWindow::clearCustomPlot (QCustomPlot* customPlot)
{
  customPlot->clearFocus ();
  customPlot->clearGraphs ();
  customPlot->clearItems ();
  customPlot->clearMask ();
  customPlot->clearPlottables ();

  // Remove the second column
//    customPlot->plotLayout ()->remove (plot_functions_CustomPlot->plotLayout ()->element (0, 1));
  // Force layout reflow
//    customPlot->plotLayout ()->simplify ();

  customPlot->replot ();
}


void
MainWindow::updateCustomPlot (QCustomPlot* customPlot)
{
  using namespace Config::GUI::PlotParams;
  using std::function;
  using std::placeholders::_1;


  qDebug () << "updateCustomPlot";

  const QVector<QColor> colors {
    Qt::blue, Qt::darkCyan, Qt::red, Qt::darkMagenta,
    Qt::green, Qt::darkGreen, Qt::darkYellow
  };

  const int samplesCount (
    std::round (
      double (Resolution) * (wndParam_B_ - wndParam_A_) + 1.
    )
  );

//  qDebug () << "samplesCount ==" << samplesCount;

  const function<Math::Float (Math::Float)> f (
    std::bind (
      Math::f,
      _1, funcParam_alpha_, funcParam_beta_, funcParam_gamma_,
      funcParam_delta_, funcParam_epsilon_, funcParam_mu_
    )
  );

  const function<Math::Float (Math::Float)> d_f (
    std::bind (
      Math::d, f, _1, interpParam_delta_
    )
  );

  const Math::NewtonPolynomial P_n (
    f, wndParam_A_, wndParam_B_, interpParam_n_
  );

  const function<Math::Float (Math::Float)> d_P_n (
    std::bind (
      Math::d,
      P_n,
      std::bind (
        Math::lerp,
        wndParam_A_, 0, wndParam_B_, interpParam_n_ - 1, _1
      ),
      interpParam_delta_
    )
  );

  const function<Math::Float (Math::Float)> r_n (
    std::bind (
      Math::r_n,
      f, P_n, _1,
      std::bind (
        Math::lerp,
        wndParam_A_, 0, wndParam_B_, interpParam_n_ - 1, _1
      )
    )
  );

  clearCustomPlot (customPlot);

  if (isFunctionTypeEnabled (Math::FunctionType::f))
  {
    plotFunction (
      f, samplesCount, wndParam_A_, wndParam_B_, wndParam_C_, wndParam_D_,
      colors[0], customPlot, QStringLiteral ("f(x)")
    );
  }

  if (isFunctionTypeEnabled (Math::FunctionType::d_f))
  {
    plotFunction (
      d_f, samplesCount, wndParam_A_, wndParam_B_, wndParam_C_, wndParam_D_,
      colors[1], customPlot, QStringLiteral ("∂f(x)")
    );
  }

  if (isFunctionTypeEnabled (Math::FunctionType::P_n))
  {
    plotPolynomial (
      P_n, samplesCount, interpParam_n_, wndParam_A_, wndParam_B_, wndParam_C_,
      wndParam_D_, colors[2], customPlot, QStringLiteral ("Pₙ(x)")
    );
  }

  if (isFunctionTypeEnabled (Math::FunctionType::d_P_n))
  {
    plotFunction (
      d_P_n, samplesCount, wndParam_A_, wndParam_B_, wndParam_C_, wndParam_D_,
      colors[3], customPlot, QStringLiteral ("∂Pₙ(x)")
    );
  }

  if (isFunctionTypeEnabled (Math::FunctionType::r_n))
  {
    plotFunction (
      r_n, samplesCount, wndParam_A_, wndParam_B_, wndParam_C_, wndParam_D_,
      colors[6], customPlot, QStringLiteral ("rₙ(x)")
    );
  }

  plotBoundingBox (
    wndParam_A_, wndParam_B_, wndParam_C_, wndParam_D_,
    Qt::darkGray, customPlot
  );

  plotMax (r_n, samplesCount, wndParam_A_, wndParam_B_, colors[4], customPlot);

  customPlot->rescaleAxes (true);

  customPlot->xAxis->setRange (wndParam_A_ - Margin, wndParam_B_ + Margin);
  customPlot->yAxis->setRange (wndParam_C_ - Margin, wndParam_D_ + Margin);

  customPlot->replot ();
}


void
MainWindow::plotFunction (
  const std::function<Math::Float (Math::Float)>& func, int samplesCount,
  double keyStart, double keyEnd, double valueStart, double valueEnd,
  const QColor& color, QCustomPlot* customPlot, const QString& name
)
{
  QVector<double> keys (samplesCount), values (samplesCount);

  for (int sampleIdx (0); sampleIdx < samplesCount; ++sampleIdx)
  {
    const double key (
      Math::lerp (
        0, keyStart,
        samplesCount - 1, keyEnd,
        sampleIdx
      )
    );
    const double value (func (key));

    keys[sampleIdx] = key;

    // FIXME: [~-]
    if (std::isnan (value))
    {
      values[sampleIdx] = std::numeric_limits<double>::quiet_NaN ();
    }
    else
    {
      values[sampleIdx] = double (Math::clamp (valueStart, valueEnd, value));
    }
  }

  QCPGraph* const graph (customPlot->addGraph ());
  graph->setData (keys, values);
  graph->setPen (QPen (color));
  graph->setSelectedPen (
    QPen (QBrush (color), Config::GUI::PlotParams::SelectedPenWidth)
  );
//  graph->setAdaptiveSampling (true);
  graph->setName (name);

//  customPlot->replot ();
}


void
MainWindow::plotPolynomial (
  const std::function<Math::Float (Math::Float)>& func, int samplesCount, int stepsCount,
  double keyStart, double keyEnd, double valueStart, double valueEnd,
  const QColor& color, QCustomPlot* customPlot, const QString& name
)
{
  QVector<double> keys (samplesCount), values (samplesCount);

  for (int sampleIdx (0); sampleIdx < samplesCount; ++sampleIdx)
  {
    const double key (
      Math::lerp (
        0, keyStart,
        samplesCount - 1, keyEnd,
        sampleIdx
      )
    );

    const double value (
      func (
        Math::lerp (
          0, 0,
          samplesCount - 1, stepsCount - 1,
          sampleIdx
        )
      )
    );

    keys[sampleIdx] = key;

    // FIXME: [~-]
    if (std::isnan (value))
    {
      values[sampleIdx] = std::numeric_limits<double>::quiet_NaN ();
    }
    else
    {
      values[sampleIdx] = double (Math::clamp (valueStart, valueEnd, value));
    }
  }

  QCPGraph* const graph (customPlot->addGraph ());
  graph->setData (keys, values);
  graph->setPen (QPen (color));
  graph->setSelectedPen (
    QPen (QBrush (color), Config::GUI::PlotParams::SelectedPenWidth)
  );
//  graph->setAdaptiveSampling (true);
  graph->setName (name);

  //  customPlot->replot ();
}


void
MainWindow::plotBoundingBox (
  double keyStart, double keyEnd, double valueStart, double valueEnd,
  const QColor& color, QCustomPlot* customPlot
)
{
  QCPItemStraightLine* const top (new QCPItemStraightLine (customPlot));
  top->setPen (QPen (color));
  top->point1->setCoords (keyStart, valueEnd);
  top->point2->setCoords (keyEnd, valueEnd);
  top->setSelectable (false);
  top->setPen (QPen (Qt::DashLine));
  customPlot->addItem (top);

  QCPItemStraightLine* const bot (new QCPItemStraightLine (customPlot));
  bot->setPen (QPen (color));
  bot->point1->setCoords (keyStart, valueStart);
  bot->point2->setCoords (keyEnd, valueStart);
  bot->setSelectable (false);
  bot->setPen (QPen (Qt::DashLine));
  customPlot->addItem (bot);

  QCPItemStraightLine* const left (new QCPItemStraightLine (customPlot));
  left->setPen (QPen (color));
  left->point1->setCoords (keyStart, valueStart);
  left->point2->setCoords (keyStart, valueEnd);
  left->setSelectable (false);
  left->setPen (QPen (Qt::DashLine));
  customPlot->addItem (left);

  QCPItemStraightLine* const right (new QCPItemStraightLine (customPlot));
  right->setPen (QPen (color));
  right->point1->setCoords (keyEnd, valueStart);
  right->point2->setCoords (keyEnd, valueEnd);
  right->setSelectable (false);
  right->setPen (QPen (Qt::DashLine));
  customPlot->addItem (right);
}


void
MainWindow::plotMax (
  const std::function<Math::Float (Math::Float)>& func, int samplesCount,
  double keyStart, double keyEnd, const QColor& color,
  QCustomPlot* customPlot
)
{
  double maxKey (0), maxValue (0);

  for (int sampleIdx (0); sampleIdx < samplesCount; ++sampleIdx)
  {
    const double key (
      Math::lerp (
        0, keyStart,
        samplesCount - 1, keyEnd,
        sampleIdx
      )
    );
    const double value (func (key));

    if (std::abs (value) > std::abs (maxValue))
    {
      maxValue = value;
      maxKey = key;
    }
  }

  QCPItemStraightLine* const line (new QCPItemStraightLine (customPlot));
  line->setPen (QPen (color));
  line->setSelectedPen (
    QPen (QBrush (color), Config::GUI::PlotParams::SelectedPenWidth)
  );
  line->point1->setCoords (maxKey, -1);
  line->point2->setCoords (maxKey, 1);
  line->setSelectable (true);
  customPlot->addItem (line);

  // TODO: [~+] Fix ellipse size (it stretches along w/ the plot axes).
  QCPItemEllipse* const ellipse (new QCPItemEllipse (customPlot));
  ellipse->topLeft->setType (QCPItemPosition::ptPlotCoords);
  ellipse->topLeft->setCoords (maxKey - .0075, .0075);
  ellipse->bottomRight->setType (QCPItemPosition::ptPlotCoords);
  ellipse->bottomRight->setCoords (maxKey + .0075, -.0075);
  // TODO: [~-] Do not use solid fill.
  ellipse->setPen (QPen (Qt::magenta));
  ellipse->setSelectedPen (
    QPen (QBrush (Qt::magenta), Config::GUI::PlotParams::SelectedPenWidth)
  );
  ellipse->setBrush (QBrush (Qt::magenta));
  ellipse->setSelectedBrush (QBrush (Qt::magenta));
  customPlot->addItem (ellipse);

  ui_->prop_x_0_LcdNumber->display (maxKey);
  ui_->prop_delta_LcdNumber->display (maxValue);
}

#pragma endregion // private methods
