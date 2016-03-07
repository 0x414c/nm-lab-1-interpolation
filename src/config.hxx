#ifndef CONFIG_HXX
#define CONFIG_HXX


#include "math/numerictypes.hxx"


namespace Config
{
  namespace GUI
  {
    namespace Defaults
    {
      constexpr double Alpha = 0.;
      constexpr double Beta = 0.;
      constexpr double Gamma = 0.;
      constexpr double Delta = .25;
      constexpr double Epsilon = .5;
      constexpr double Mu = 1.;

      constexpr double A = -2.5;
      constexpr double B = 2.5;
      constexpr double C = -5.;
      constexpr double D = 5.;

      constexpr int N = 20;
      constexpr int DeltaExponent = -4;

      constexpr bool LiveUpdateEnabled = false;
    }


    namespace Limits
    {
      constexpr double ABCD_Min = -100.;
      constexpr double ABCD_Max = 100.;
    }


    namespace PlotParams
    {
      constexpr int PlotResolution = 100;

      constexpr double SelectedPenWidth = 2.;

      constexpr int FontSize = 9;
    }
  }


  namespace MathConstants
  {
    constexpr Math::Float FuzzyComparisonEpsilon = 1E-9;
  }
}


#endif // CONFIG_HXX
