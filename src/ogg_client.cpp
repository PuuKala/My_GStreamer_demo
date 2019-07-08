// GStreamer ogg muxed audio video stream client ogg_client.cpp

#include <iostream>
#include <string>

#include <gst/gst.h>

#define NEVER_TIMEOUT GST_CLOCK_TIME_NONE

int main(int argc, char *argv[]) {
  // Check if the given arguments are ok
  if (argc < 2) {
    std::cout << "Give the IP-address as the argument" << std::endl;
    return EXIT_SUCCESS;
  } else if (argc > 2) {
    std::cout << "Incorrect amount of arguments. Give only the IP-address as "
                 "the argument"
              << std::endl;
    return EXIT_SUCCESS;
  }
  std::string server_ip = argv[1];

  // Initialize GStreamer, construct pipeline and get the bus from pipeline
  gst_init(nullptr, nullptr);
  GstElement *pipe = gst_parse_launch(
      // Connection to server
      ("tcpclientsrc host=" + server_ip + " port=10000 ! " +

       // From mux to audiosink
       "oggdemux name=mux ! queue ! vorbisdec ! audioconvert ! autoaudiosink " +

       // From mux to videosink
       "mux. ! queue ! theoradec ! videoconvert ! autovideosink")
          .c_str(),
      nullptr);
  GstBus *bus = gst_element_get_bus(pipe);

  // Start playing and wait for error or end-of-service message
  if (gst_element_set_state(pipe, GST_STATE_PLAYING))
    gst_bus_timed_pop_filtered(
        bus, NEVER_TIMEOUT,
        (GstMessageType)(
            GST_MESSAGE_ERROR |
            GST_MESSAGE_EOS));  // Hangs here until error or end-of-service

  // Deinitialize GStreamer and its objects
  gst_element_set_state(pipe, GST_STATE_NULL);
  gst_object_unref(bus);
  gst_object_unref(pipe);
  gst_deinit();

  return EXIT_SUCCESS;
}
