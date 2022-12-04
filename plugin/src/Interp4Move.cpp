#include <iostream>
#include "Interp4Move.hh"
#include "MobileObj.hh"

using std::cout;
using std::endl;

extern "C"
{
  Interp4Command *CreateCmd(void);
  const char *GetCmdName() { return "Move"; }
}

/*!
 * \brief
 *
 *
 */
Interp4Command *CreateCmd(void)
{
  return Interp4Move::CreateCmd();
}

/*!
 *
 */
Interp4Move::Interp4Move() : _Object_name(""), _Speed_mmS(0), _Distance_m(0)
{
}

/*!
 *
 */
void Interp4Move::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _Object_name << " " << _Speed_mmS << " " << _Distance_m << endl;
}

/*!
 *
 */
const char *Interp4Move::GetCmdName() const
{
  return ::GetCmdName();
}

/*!
 *
 */
bool Interp4Move::ExecCmd(Scene *scene) const
{
  MobileObj *object = scene->FindMobileObj(_Object_name.c_str());
  Vector3D position_init = object->GetPositoin_m();
  double roll_init = object->GetAng_Roll_deg();
  double pitch_init = object->GetAng_Pitch_deg();
  double yaw_init = object->GetAng_Yaw_deg();

  double time = _Distance_m / (_Speed_mmS / 1000);
  double steps = (int)(time * FPS);

  double x_move = 0, y_move = 0, z_move = 0;
  Vector3D move;
  double step_distance = _Distance_m / steps;
  double step_time = 1 / FPS;

  for (int i = 0; i < steps; ++i)
  {
    x_move += step_distance * cos(pitch_init * M_PI / 180) * cos(yaw_init * M_PI / 180);
    y_move += step_distance * (cos(roll_init * M_PI / 180) * sin(yaw_init * M_PI / 180) + cos(yaw_init * M_PI / 180) * sin(pitch_init * M_PI / 180) * sin(roll_init * M_PI / 180));
    z_move += step_distance * (sin(roll_init * M_PI / 180) * sin(yaw_init * M_PI / 180) - cos(roll_init * M_PI / 180) * cos(yaw_init * M_PI / 180) * sin(pitch_init * M_PI / 180));
    move[0] = x_move + position_init[0];
    move[1] = y_move + position_init[1];
    move[2] = z_move + position_init[2];
    scene->LockAccess(); // Lock access
    object->SetPosition_m(move);
    scene->MarkChange();
    scene->UnlockAccess();
    usleep(step_time * 1000000);
  }
  // math errors correction
  step_distance = _Distance_m - (steps * step_distance);
  if (step_distance)
  {
    x_move += step_distance * cos(pitch_init * M_PI / 180) * cos(yaw_init * M_PI / 180);
    y_move += step_distance * (cos(roll_init * M_PI / 180) * sin(yaw_init * M_PI / 180) + cos(yaw_init * M_PI / 180) * sin(pitch_init * M_PI / 180) * sin(roll_init * M_PI / 180));
    z_move += step_distance * (sin(roll_init * M_PI / 180) * sin(yaw_init * M_PI / 180) - cos(roll_init * M_PI / 180) * cos(yaw_init * M_PI / 180) * sin(pitch_init * M_PI / 180));
    move[0] = x_move + position_init[0];
    move[1] = y_move + position_init[1];
    move[2] = z_move + position_init[2];
    scene->LockAccess(); // Lock access
    object->SetPosition_m(move);
    scene->MarkChange();
    scene->UnlockAccess();
  }

  return true;
}

/*!
 *
 */
bool Interp4Move::ReadParams(std::istream &Strm_CmdsList)
{
  if (!(Strm_CmdsList >> _Object_name))
  {
    std::cout << "Blad wczytywania nazwy obiektu" << std::endl;
    return 1;
  }

  if (!(Strm_CmdsList >> _Speed_mmS))
  {
    std::cout << "Blad wczytywania predkosci obiektu" << std::endl;
    return 1;
  }

  if (!(Strm_CmdsList >> _Distance_m))
  {
    std::cout << "Blad wczytywania odleglosci" << std::endl;
    return 1;
  }
  return 0;
}

/*!
 *
 */
Interp4Command *Interp4Move::CreateCmd()
{
  return new Interp4Move();
}

/*!
 *
 */
void Interp4Move::PrintSyntax() const
{
  cout << "   Move  NazwaObiektu  Szybkosc[m/s]  DlugoscDrogi[m]" << endl;
}
