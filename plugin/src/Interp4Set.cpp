#include <iostream>
#include "Interp4Set.hh"
#include "MobileObj.hh"

using std::cout;
using std::endl;

extern "C"
{
  Interp4Command *CreateCmd(void);
  const char *GetCmdName() { return "Set"; }
}

/*!
 * \brief
 *
 *
 */
Interp4Command *CreateCmd(void)
{
  return Interp4Set::CreateCmd();
}

/*!
 *
 */
Interp4Set::Interp4Set() : _Object_name(""), _X(0), _Y(0), _Angle_deg(0)
{
}

/*!
 *
 */
void Interp4Set::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _Object_name << " " << _X << " " << _Y << " " << _Angle_deg << endl;
}

/*!
 *
 */
const char *Interp4Set::GetCmdName() const
{
  return ::GetCmdName();
}

/*!
 *
 */
bool Interp4Set::ExecCmd(Scene *scene) const
{
  MobileObj *object = scene->FindMobileObj(_Object_name.c_str());
  Vector3D position_init = object->GetPositoin_m();
  Vector3D new_position;
  new_position[0] = _X;
  new_position[1] = _Y;
  new_position[2] = position_init[2];
  scene->LockAccess();

  object->SetPosition_m(new_position);
  object->SetAng_Yaw_deg(_Angle_deg);

  scene->MarkChange();
  scene->UnlockAccess();
  return true;
}

/*!
 *
 */
bool Interp4Set::ReadParams(std::istream &Strm_CmdsList)
{
  if (!(Strm_CmdsList >> _Object_name))
  {
    std::cout << "Blad wczytywania nazwy obiektu" << std::endl;
    return 1;
  }

  if (!(Strm_CmdsList >> _X))
  {
    std::cout << "Blad wczytywania wspolrzednej x" << std::endl;
    return 1;
  }

  if (!(Strm_CmdsList >> _Y))
  {
    std::cout << "Blad wczytywania wspolrzednej y" << std::endl;
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
Interp4Command *Interp4Set::CreateCmd()
{
  return new Interp4Set();
}

/*!
 *
 */
void Interp4Set::PrintSyntax() const
{
  cout << "   Set  NazwaObiektu  WspX  WspY  KatOZ" << endl;
}
