# My_GStreamer_demo
For the CV of Sami Karkinen  
  
  
## Installation instructions for building:
Run the following line:  
```sudo apt install cmake```  
Get Cerbero from git to your home directory or \~/git with line:  
```git clone https://gitlab.freedesktop.org/gstreamer/cerbero```  
Add cerbero as command to bash:  
```echo "alias cerbero='~/git/cerbero/cerbero-uninstalled'" >> ~/.bashrc```  
    OR if you git cloned directly to home directory:  
```echo "alias cerbero='~/cerbero/cerbero-uninstalled'" >> ~/.bashrc```  
    In case you need sudo to run cerbero-uninstalled, you might have to replace all 'cerbero' commands with:  
```sudo <cerbero-directory>/cerbero-uninstalled```  
    OR modify the .bashrc line you wrote above to:  
```alias cerbero='sudo ~/cerbero/cerbero-uninstalled'```  
  
Run Cerbero bootstrap with line:  
```cerbero bootstrap```  
- NOTE: You might need sudo for this. See the installation step above for additional information.  
- NOTE: Bootstrap takes quite a while. If the program fails and asks whether to abort or retry, retry from the failed step
    (option 2)  
<a/>
Run the following line:  
```cerbero build gstreamer-1.0 gst-plugins-base-1.0 gst-plugins-good-1.0```  
- NOTE: This takes quite a while. If the program fails and asks whether to abort or retry, retry from the failed step
    (option 2)  
<a/>
Run create_and_build.sh  
  
  
## Usage:
### GST_visualizer_demo:
Have some music playing in the background  
Run Cerbero shell with line:  
```cerbero shell```  
Run GST_visualizer_demo in the Cerbero shell in the build folder with line:  
```./GST_visualizer_demo```  
    You can also add --bluetooth as an added parameter to search for bluetooth device instead of the default speakers.  
- NOTE: GST_visualizer_demo also has a TCP server sending the visualization as ogg encoded data. You can receive this with
    GST_ogg_client or by hosting GStreamer_HTML_demo.html on the same machine as the GST_visualizer_demo is running.  
  
  
#### The following programs need GST_visualizer_demo running

### GST_ogg_client:
Run Cerbero shell with line:  
```cerbero shell```  
Run GST_ogg_client in the Cerbero shell with the server IP-address as an added parameter  
```For example: ./GST_ogg_client 127.0.0.1```  
  
### GStreamer_HTML_demo.html:
Host the .html file in a webserver of your choice(for example node) on the same machine as you're running GST_visualizer_demo Open Firefox or Edge, connect to the webserver and push the play button if needed.
