----------
Touchradio
----------

Touchradio offers a modern and fluid user interface, designed to be used with a touchscreen allowing to control a player connected to a server Logitech Media Server.

------------
Key features
------------

* Basic playback controls: Play, pause, previous, next, volume
* Browse the music library (library and favorites)
* Display the album cover
* Display information about the currently playing track (cover, artist, album, title,...)
* Modern and fluid UI, design to be used with a touchscreen
* Designed and developped on a RaspberryPi, but should work as well on any platform compatible with Qt5.

------------
Architecture
------------
Touchradio is only one component of a set composed of:

* An audio streaming server : [Logitech Media Server (LMS)](http://en.wikipedia.org/wiki/Logitech_Media_Server)
* A player for LMS : [Squeezelite] (https://code.google.com/p/squeezelite/).
* A graphical user interface allowing to control both of them : Touchradio/

Touchradio is a graphical frontend that allows to connect to LMS and to a player in order to control the playback of the tracks and web streams.
[LMS] (http://en.wikipedia.org/wiki/Logitech_Media_Server) is developped by Logitech to support the product range named Squeezebox. This product line is composend of several Squeezebox models that can connect to a LMS server. This allows the users to have multiple players connected to a personnal server. And this server stores the whole music library which will be shared among all connected players.

These are commercial products, but Logitech decided to distribute the source code of LMS under the terms of the [GNU General Public License] (http://en.wikipedia.org/wiki/GNU_General_Public_License). Therefore, the open-source world has access to the source code and the documentation of the server. LMS is available on multiple platforms like Windows, Mac OS, Linux, and, of cours, Linux ARM and on the RapsberryPi!
LMS offers a very complete web interface which allows to control the playback on each Squeezebox, browse the lirbary, ...

[Squeezelite] (https://code.google.com/p/squeezelite/), is a headless Squeezebox emulator. It is a software that acts like a Squeezebox to the Logitech Media Server. Squeezelite handles the playback of the audio streams coming from the LMS on the audio interface of the running system. Squeezelite runs headless, but it is possible to control it via LMS and a CLI API.

Touchradio uses the functionalities of both of these open-source software to allow the users to control a Squeezebox-like player.

--------
Historic
--------
I first thought about this project when my little tuner-CD I used in my kitech broke down. A that time, I had several solution : I could buy a new simple tuner-cd but... FM radio and CD are not fashion any more. Now, every one listens to its MP3 files and web streams!
Then, I tried to use my smartphone and ipod but it was not very handful: I spent all my time to connect and disconnect the devices, unlock them to set the volume up and down, and I don't tell you about autonomy problems...

At that time, I received my first RaspberryPi. Id did not take long for me until I found it a usefule and practical use! I'm going to build my kitchen radio based on a RasberrpyPi, which will allow me to play my whole music library and web streams!

I did a lot of research and analysis: I had to find a suitable [touchscreen] (http://blog.slashome.fr.cr/posts/un-ecran-tactile-hdmi-pour-le-raspberrypi.html), a [suitable graphical framework] (http://blog.slashome.fr.cr/posts/touchradio-passage-a-qt5.html), the underlying audio system (I finally choose LMS and Squeezelite, but I also tried OMXPlayer and MPD, for example).

Finally, once I did all these choices and tested them, I switched to the development phase of this first prototype. Of course, this is not a very big and complicated project, but it is not easy to find free time and motivation after a 8 hours coding day at work, and without neglecting my private life, my hobbys and my other projects.

-----------
Development
-----------
Touchradio is based on [Qt5] (http://qt-project.org/qt5) and [QtQuick2] (http://qt-project.org/doc/qt-5.0/qtquick/qtquick-index.html). Because Qt5 is a multi platform library, Touchradio should work on any system compatible with Qt5/QtQuick. I choose Qt5 because of its graphical functionalities oriented to mobile and touch applications, and its support for the RaspberryPi.
The whole source code is written in C++, without any other dependance.

--------------------
State of the project
--------------------
The project is still under heavy development. The current state of the project is a demo prototype. It implements basics functionalities, but it is not complet and certainly full of bugs. And I discourge anyone who would like to use the code right now : It is awful, and I would never dare write such kind of code at work! My first goal was to make this first prototype no matter what, to see that I could do it. Now I did it, I'll do a lot of refactoring.

Touchradio is working. I use it in my lounge and in my kitchen since the project is able to run correctly, and I appreciate every new improvement I make to the software every day. However, it is not ready yet to be used by an end user, who is looking solution that is working out of the box. For now, the software is not very flexible (in terms of network configuration, and screen size, for example).

However, if you're interested in this project, feel free to give me your thoughts about it, to help me improve it, add functionalities,...

And, as you certainly noticed on the pictures, the mecanical part is reduced to its simplest expression: The case is a wood beer rack, which dimensions fit perfectly with the size of my touchscreen! And I think the wiring could be reviewed... As I'm not a mecanical designer, if you have any suggestions to pack the set in a more esthetical fashion, they are welcome!

