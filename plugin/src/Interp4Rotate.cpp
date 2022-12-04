#include <iostream>
#include "Interp4Rotate.hh"
#include "MobileObj.hh"

using std::cout;
using std::endl;

extern "C"
{
  Interp4Command *CreateCmd(void);
  const char *GetCmdName() { return "Rotate"; }
}

/*!
 * \brief
 *
 *
 */
Interp4Command *CreateCmd(void)
{
  return Interp4Rotate::CreateCmd();
}

/*!
 *
 */
Interp4Rotate::Interp4Rotate() : _Object_name(""), _Angular_speed_degs(0), _Angle_deg(0)
{
}

/*!
 *
 */
void Interp4Rotate::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _Object_name << " " << _Angular_speed_degs << " " << _Angle_deg << endl;
}

/*!
 *
 */
const char *Interp4Rotate::GetCmdName() const
{
  return ::GetCmdName();
}

/*!
 *
 */
bool Interp4Rotate::ExecCmd(Scene *scene) const
{
  MobileObj *object = scene->FindMobileObj(_Object_name.c_str());
  // Vector3D position_init = object->GetPositoin_m();
  // double roll_init = object->GetAng_Roll_deg();
  // double pitch_init = object->GetAng_Pitch_deg();
  double yaw_init = object->GetAng_Yaw_deg();

  double time = _Angle_deg / _Angular_speed_degs;
  double steps = (int)(time * FPS);
  double step_distance = _Angle_deg / steps;
  double step_time = 1 / FPS;

  // double startYaw = object->GetAng_Yaw_deg();
  double yaw_move = 0;

  for (int i = 0; i < steps; ++i)
  {
    scene->LockAccess(); // Lock access to the scene to modify something :)
    yaw_move += step_distance;
    object->SetAng_Yaw_deg(yaw_init + yaw_move);
    scene->MarkChange();
    scene->UnlockAccess();
    usleep(step_time * 1000000);
  }
  return true;
}

/*!
 *
 */
bool Interp4Rotate::ReadParams(std::istream &Strm_CmdsList)
{
  if (!(Strm_CmdsList >> _Object_name))
  {
    std::cout << "Blad wczytywania nazwy obiektu" << std::endl;
    return 1;
  }

  if (!(Strm_CmdsList >> _Angular_speed_degs))
  {
    std::cout << "Blad wczytywania predkosci katowej obiektu" << std::endl;
    return 1;
  }

  if (!(Strm_CmdsList >> _Angle_deg))
  {
    std::cout << "Blad wczytywania kata" << std::endl;
    return 1;
  }
  return 0;
}

/*!
 *
 */
Interp4Command *Interp4Rotate::CreateCmd()
{
  return new Interp4Rotate();
}

/*!
 *
 */
void Interp4Rotate::PrintSyntax() const
{
  cout << "   Move  NazwaObiektu  SzybkoscKatowa[deg/s]  KatObrotu[deg]" << endl;
}
