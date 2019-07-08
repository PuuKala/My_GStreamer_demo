/* AVStream class implementation AVStream.cpp
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
 *  1a. Outright copyright infringement - Don't just copy this and change the name.
 *  1b. Selling the unmodified original with no work done what-so-ever, that's REALLY being a dick.
 *  1c. Modifying the original work to contain hidden harmful content. That would make you a PROPER dick.
 *
 * 2. If you become rich through modifications, related works/services, or supporting the original work,
 * share the love. Only a dick would make loads off this work and not buy the original work's
 * creator(s) a pint.
 *
 * 3. Code is provided with no warranty. Using somebody else's code and bitching when it goes wrong makes
 * you a DONKEY dick. Fix the problem yourself. A non-dick would submit the fix back.
 */

#include "AVStream.h"

#define NEVER_TIMEOUT GST_CLOCK_TIME_NONE

/**
 * @brief Takes given device name and saves it as private variable.
 * Also initializes GStreamer and sets the AVStream state to init.
 */
AVStream::AVStream(std::string &device)
    : _device(device), _state(kStateInit), _running(true) {
  gst_init(nullptr, nullptr);
}

/**
 * @brief Deinitializes GStreamer and its objects
 */
AVStream::~AVStream() {
  gst_element_set_state(_pipe, GST_STATE_NULL);
  gst_object_unref(_bus);
  gst_object_unref(_pipe);
  gst_deinit();
}

/**
 * @brief The state machine function
 * @details Initializes the GStreamer pipeline and bus on init state.
 * Plays the pipeline and waits for error or end-of-service message on playing
 * state. Goes to init state when exiting playing state and vice versa. Hangs on
 * message wait aka. there is no exit other than Ctrl-C from command line.
 */
void AVStream::StateMachine() {
  switch (_state) {
    case kStateInit:
      _pipe = gst_parse_launch(
          // From audio monitor to local video
          ("pulsesrc device=" + _device +
           " ! tee name=t1 ! goom ! tee name=t2 ! queue ! videoconvert !"
           "autovideosink "

           // From visualization to tcpserversink
           "t2. ! videoconvert ! theoraenc ! queue ! oggmux name=mux ! "
           "tcpserversink host=0.0.0.0 port=10000 "

           // From audio monitor to oggmux
           "t1. ! queue ! audioconvert ! vorbisenc ! mux.")
              .c_str(),
          nullptr);
      _bus = gst_element_get_bus(_pipe);
      _state = kStatePlaying;
      break;

    case kStatePlaying:
      if (gst_element_set_state(_pipe, GST_STATE_PLAYING))
        gst_bus_timed_pop_filtered(
            _bus, NEVER_TIMEOUT,
            (GstMessageType)(
                GST_MESSAGE_ERROR |
                GST_MESSAGE_EOS));  // Hangs here until error or end-of-service
      gst_element_set_state(_pipe, GST_STATE_NULL);
      _running = false;
      break;
  }
}

/**
 * @brief Run state machine in a loop
 */
void AVStream::run() {
  while (_running) {
    StateMachine();
  }
}
