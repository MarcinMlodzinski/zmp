#pragma once

#include "Vector3D.hh"
#include <string>

class MobileObjConfig {
public:
  std::string name;
  Vector3D scale;
  Vector3D rgb;
  Vector3D shift;
  Vector3D rot;
  Vector3D trans;
};