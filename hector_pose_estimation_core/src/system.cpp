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

#include <hector_pose_estimation/system.h>
#include <hector_pose_estimation/pose_estimation.h>
#include <bfl/filter/kalmanfilter.h>

namespace hector_pose_estimation {

System::System(SystemModel *model, const std::string &name)
  : model_(model)
  , name_(name)
  , status_flags_(0)
  , prior_(StateDimension)
{
  model_->getPrior(prior_);
  parameters_.add(model_->parameters());
}

System::~System() {
  delete model_;
}

bool System::init()
{
  return true;
}

void System::cleanup()
{
}

void System::reset()
{
  init();
}

bool System::update(PoseEstimation &estimator, double dt) {
  ROS_DEBUG("Updating with system model %s", getName().c_str());

  // std::cout << "[" << getName() << "] input    = [" << input_.transpose() << "]" << std::endl;

  model_->set_dt(dt);
  model_->setMeasurementStatus(estimator.getMeasurementStatus());
  estimator.filter()->Update(model_, input_);
  updated();
  estimator.updated();

  return true;
}

void System::updated() {
  if (getModel()) status_flags_ = getModel()->getStatusFlags();
}

StateVector System::limitState(StateVector state) const {
  model_->Limit(state);
  return state;
}

} // namespace hector_pose_estimation
