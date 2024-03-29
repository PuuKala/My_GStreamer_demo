/* AVStream class definitions stream.h
 *
 * DON'T BE A DICK PUBLIC LICENSE
 *
 * > Version 1.1, December 2016
 *
 * > Copyright (C) 2019 Sami Karkinen
 *
 * Everyone is permitted to copy and distribute verbatim or modified
 * copies of this license document.
 *
 * > DON'T BE A DICK PUBLIC LICENSE
 * > TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 *
 * 1. Do whatever you like with the original work, just don't be a dick.
 *
 *    Being a dick includes - but is not limited to - the following instances:
 *
 *  1a. Outright copyright infringement - Don't just copy this and change the
 * name. 1b. Selling the unmodified original with no work done what-so-ever,
 * that's REALLY being a dick. 1c. Modifying the original work to contain hidden
 * harmful content. That would make you a PROPER dick.
 *
 * 2. If you become rich through modifications, related works/services, or
 * supporting the original work, share the love. Only a dick would make loads
 * off this work and not buy the original work's creator(s) a pint.
 *
 * 3. Code is provided with no warranty. Using somebody else's code and bitching
 * when it goes wrong makes you a DONKEY dick. Fix the problem yourself. A
 * non-dick would submit the fix back.
 */

#pragma once
#ifndef STREAM_H
#define STREAM_H

#include <string>

#include <gst/gst.h>

class AVStream {
  enum StreamState { kStateInit, kStatePlaying };  // States of the AVStream
 public:
  // Constructor, requires pulse device name as the parameter
  AVStream(std::string &device);
  ~AVStream();
  void run();  // Runs and hangs on playing
 private:
  bool _running;
  std::string _device;
  GstElement *_pipe;
  GstBus *_bus;
  StreamState _state;
  void StateMachine();
};

#endif