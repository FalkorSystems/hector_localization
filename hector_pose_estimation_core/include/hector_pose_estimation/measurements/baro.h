//=================================================================================================
// Copyright (c) 2011, Johannes Meyer, TU Darmstadt
// All rights reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the Flight Systems and Automatic Control group,
//       TU Darmstadt, nor the names of its contributors may be used to
//       endorse or promote products derived from this software without
//       specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//=================================================================================================

#ifndef HECTOR_POSE_ESTIMATION_BARO_H
#define HECTOR_POSE_ESTIMATION_BARO_H

#include <hector_pose_estimation/measurement.h>
#include <bfl/wrappers/matrix/matrix_wrapper.h>
#include "height.h"

namespace hector_pose_estimation {

class BaroModel : public HeightModel
{
public:
  BaroModel();
  virtual ~BaroModel();

  virtual ColumnVector ExpectedValueGet() const;
  virtual Matrix dfGet(unsigned int i) const;

  void setQnh(double qnh) { qnh_ = qnh; }
  double getQnh() const { return qnh_; }

protected:
  double qnh_;
};

class Baro : public Measurement_<BaroModel>
{
public:
  Baro(const std::string& name = "baro") : Measurement_<BaroModel>(name) {}
  virtual ~Baro() {}

  void reset(const StateVector& state);

  void setElevation(double elevation) { getModel()->setElevation(elevation); }
  double getElevation() const { return getModel()->getElevation(); }

  void setQnh(double qnh) { getModel()->setQnh(qnh); }
  double getQnh() const { return getModel()->getQnh(); }
};

} // namespace hector_pose_estimation

#endif // HECTOR_POSE_ESTIMATION_BARO_H
