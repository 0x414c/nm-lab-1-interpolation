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
      constexpr double Delta = .5;
      constexpr double Epsilon = .5;
      constexpr double Mu = 1.;

      constexpr double A = -2.;
      constexpr double B = 2.;
      constexpr double C = -1.;
      constexpr double D = 1.;

      constexpr int N = 10;
      constexpr int DeltaExponent = -4;

      constexpr bool LiveUpdateEnabled = false;
    }


    namespace InputLimits
    {
      constexpr double ABCD_Min = -100.;
      constexpr double ABCD_Max = 100.;
    }


    namespace PlotParams
    {
      constexpr int ResolutionMultiplier = 2;

      constexpr double Margins = .25;

      constexpr double SelectedPenWidth = 2.;

      constexpr int FontSize = 9;
    }
  }


  namespace MathConstants
  {
    constexpr double Epsilon = 1E-16;
  }
}


#endif // CONFIG_HXX
