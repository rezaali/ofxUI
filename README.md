ofxUI
=====

A User Interface Library/Addon for openFrameworks

ofxUI is an addon for openFrameworks (version 0.8.0+) that easily allows for the creation of user interfaces aka GUIs. ofxUI also takes care of widget layout, spacing, font loading, saving and loading settings, and widget callbacks. ofxUI can be easily customized (colors, font & widget sizes, padding, layout, etc).

Featured Projects: http://www.syedrezaali.com/blog/?p=3102

ofxUI contains a collection of minimally designed graphical user interface (GUI) widgets including:

- Buttons (push, state, toggle, image, label)
- Button Matrices
- Dropdown Menus
- Labels
- Sliders (rotary, range, vertical, horizontal)
- Number Dials
- 2D Pads
- Text Input Areas
- Base Draws (ofImages, ofTexture, ofFbo, etc)
- Image Sliders
- Image Buttons
- Image Color Sampler
- Value Plotters
- Moving Graphs 
- Waveform & Spectrum Graphs
- Radio Toggles
- Text Areas
- Sortable List

This library allows for rapid UI design and development. It uses ofTrueTypeFonts for nice font rendering. Widget layout is semi-automatic, and can be easily customized. ofxUI is a GL based GUI and uses openFramework's drawings calls to render its widgets. It integrates into openFrameworks projects very easily since it was designed specifically for OF. There are many examples included in the download that show how to add widgets, customize their placement, get values from different types of widgets, set widget values, add callback functions for gui events, saving and loading settings, and more.

This UI library was inspired & influenced by: 

- controlP5 (http://www.sojamo.de/libraries/controlP5/) 
- GLV (http://mat.ucsb.edu/glv/)
- SimpleGUI (http://marcinignac.com/blog/simplegui/)
- Apple's User Interface 

It has been tested on OSX and iOS (OF 073+). It should work on linux and windows, since its only dependency is openFrameworks & ofxXmlSettings. ofxUI is open source under an MIT License, therefore you can use it in commercial and non-commercial projects. If you do end up using it, please let me know. I would love to see more examples of it out there in the wild. If you plan to use it in a commercial project please consider donating to help support this addon and future releases/fixes/features (http://www.syedrezaali.com/blog/?p=2172).

In terms of performance, I haven't compared it to other GUIs out there, but since its written using OF drawing calls and uses Listeners built in to OF, it run very fast and doesn't take a lot of CPU cycles...atleast when I tested it when my sketches. On my laptop (Apple Macbook Pro 2009) without vertical sync the all widgets example runs upwards of ~350 fps. 

On a personal note: I designed ofxUI so that if I present my work to a client or put out an App on the App store, it would have a decent aesthetic and be presentable to non-hackers/programmers. I really like the widgets in MaxMsp, so I wanted to have something similar so when I prototype in C++ I could easily go about creating a UI that is pleasing to use and works robustly. 

Additionally, I was motived to write my own since I wanted something like ControlP5 (which is easy to get up and running) for Processing for OF. I use ControlP5 a lot and love its minimal aesthetic. I also love simpleGUI for Cinder, but since I primarily code using OF, I developed ofxUI with the intentions that it needs to be minimally designed, intuitive to use, easily integrated, flexible and customizable.

When I first started programming with C++ it was difficult for me to use the other GUIs...their either depended on other libraries, which weren't included in the download, and it wouldn't work out of the box, or they were complicated to integrate into my projects. Additionally, I was motived to write my own since I wanted something like ControlP5 (which is easy to get up and running) for Processing for OF. I use ControlP5 a lot and love its minimal aesthetic. I also love simpleGUI for Cinder, but since I primarily code using OF, I developed ofxUI with the intentions that it needs to be minimally designed, intuitive to use, easily integrated, flexible and customizable.

## Requirements
- openFrameworks 0.8.0+

## Getting Started

This tutorial will provide step by step instructions on how to get started with ofxUI. For this we are going to be assuming you are using openFrameworks 0.8.0+ for OSX, however these instructions should be easily adaptable for iOS.

- After downloading or cloning ofxUI, place it in your openframeworks addons folder. 

- Create a new openframeworks project using the project generator, make sure ofxUI and ofxXmlSettings are enabled from the list of addons shown.

- Open the project in xCode. 

- Now select your ofApp.h file and add ```#include "ofxUI.h"``` under ```#include "ofMain.h"```

- Then in your ofApp.h file, create a new ```ofxUICanvas``` object within the ofApp class like so:

```cpp
ofxUICanvas *gui;
```

In addition create two functions:

```cpp
void exit(); 
void guiEvent(ofxUIEventArgs &e);
```

- Switch over to your ofApp.cpp file and define the exit and `guiEvent` functions: 

```cpp
void ofApp::exit()
{
	
}

void ofApp::guiEvent(ofxUIEventArgs &e)
{
	
}
```

- Within the setup function we are going to initialize the gui object and add widgets to it. So one way to do that is: 

```cpp
gui = new ofxUICanvas();		//Creates a canvas at (0,0) using the default width	
```

- In the exit function we have to delete the gui after we are done using the application. But before this we want to tell the GUI to save the current values in the widgets to an XML file. Thus your exit function should look like: 

```cpp
void ofApp::exit()
{
    gui->saveSettings("settings.xml");     
    delete gui; 
}
```

- We are now going to: 

	- add a slider widget to the GUI 
	- automatically size the gui to fit all the widgets
	- add an event listener to the ofApp
	- load settings from an xml file called settings.xml

```cpp
gui->addSlider("BACKGROUND",0.0,255.0,100.0); 
gui->autoSizeToFitWidgets(); 
ofAddListener(gui->newGUIEvent, this, &ofApp::guiEvent); 
gui->loadSettings("settings.xml");
```

Note: The second to last line adds a listener/callback, so the gui knows what function to call once a widget is triggered or interacted with by the user, don't worry if its doesn't make too much sense right now, you'll get the hang of it. The last line tells the gui to load settings (widget values from a saved xml file, if the file isn't present it uses the default value of the widgets). 

- Now to the `guiEvent` function, we need to react to the user input. The argument of the `guiEvent` function, ```ofxUIEventArgs &e```, contains the widget which was modified. To access the widget we do the following:

```cpp
void testApp::guiEvent(ofxUIEventArgs &e)
{
    if(e.getName() == "BACKGROUND")	
    {
        ofxUISlider *slider = e.getSlider();    
        ofBackground(slider->getScaledValue());
    }   
}
```

Note: The if statement compares the widget's name with "BACKGROUND". It does that via a string comparison. If the widget's name is "BACKGROUND", then its the slider widget we created earlier. The slider's value is retrieved by the ``` getScaledValue()``` function. 

- Lets add a toggle to toggle the window between fullscreen and window mode. In the setup function add another widget after the slider widget: 

```cpp
gui->addToggle("FULLSCREEN", false);
```

- We have to now respond to the "FULLSCREEN" toggle widget so we add more functionality to our `guiEvent` function. In the end it should look like:

```cpp
void testApp::guiEvent(ofxUIEventArgs &e)
{
    if(e.getName() == "BACKGROUND")
    {
        ofxUISlider *slider = e.getSlider();    
        ofBackground(slider->getScaledValue());
    }
    else if(e.getName() == "FULLSCREEN")
    {
        ofxUIToggle *toggle = e.getToggle(); 
        ofSetFullscreen(toggle->getValue()); 
    }    
}
```

Note: So you can see adding other kinds of widgets and reacting to them are done in a very similar manner. Explore the examples to check out how to access some of the more complex widgets and variable binding so callbacks are needed as often. I hope you'll see thats its pretty intuitive. I tried my best to limit the amount of code that needs to be written, however I kept it open enough so people can be expressive with it. 

If you lost your way somewhere in the tutorial, don't worry the whole project is included in the examples in the ofxUI addon folder!

Note: If you don't need to save/load the gui settings and don't want to include ofxXmlSettings in your project, you can set the following define in your project build settings: OFX_UI_NO_XML

ofxUI was / is developed by Reza Ali (www.syedrezaali.com || syed.reza.ali@gmail.com || @rezaali). Since its release in early 2012, its had more than 250 commits and now has 18 contributors: Camilo, obviousjim, prisonerjohn, syedhali, falcon4ever, SoylentGraham, NickHardeman, bilderbuchi, danomatika, rc1, emmanuelgeoffray, samdraz, danoli3, JohnSebastianHussey, markpitchless, kikko, and Garoe. 