# SDL Engine v0.29

Latest Changes
---------------
- Fixed DeltaTime bug in main.cpp
- Added RotateAABB in CollisionManager to show an expanding Bounding Box when Game Object is rotated
- Added RotetePoint in static Util class to support RotateAABB
- Added bounds to RigidBody to support RotateAABB
- Added isCentered boolean to GameObject class to support RotateAABB
- Adjusted sizes for ImGui Window, Main Window and Console Window.
- Fixed bug that produced Mouse events in ImGUI Window when moving or clicking mouse in Main Window.
- Updated to Current Version of SDL 2.26.2
- Updated to Current Version of SDL_mixer 2.6.2
- Updated to Current Version of SDL_image 2.6.2
- Updated to Current Version of SDL_TTF 2.20.1
- updated to Current Version of SDL_net 2.2.0
- Upgraded ImGui to latest version (v1.89.2)


Known Bugs
---------------
- UIButton Events remain a little janky when being clicked, especially when moving from to a new Scene

## Previous Versions

### v0.28
---------------
- Refactored all classes so that function names are now Upper Case
- Added Convenience functions to TextureManager to make it easier to Draw and Animate
- Added NavigationObject class
- Converted all enums to enum classes
- Updated to Current Version of SDL 2.0.22
- Updated to Current Version of SDL_TTF 2.0.18
- Upgraded ImGui to latest version (v1.87)

### v0.27
---------------
- Added **keyPressed** and **keyReleased** functions for single-frame keyboard events 
- Added **mousePressed** and **mouseReleased** for single-frame mouse events


### v0.26
---------------
- Upgraded ImGui to latest version (v1.82)
- Modified Util class to allow drawing functions to work in any window
- Fixed ImGui window not clearing bug with a hack
- Fixed EventManger Bug that would allow a button events to trigger from the ImGui window

### v0.25
---------------
- Expanded IMGUI Support so that it works in any scene in a separate window
- Changed Singletons to Magic Statics (other than FontManager -- still TODO)
- Added more Collision Check Functions in Collision Manager (e.g. LOSCheck)

### v0.24
---------------
- Added IMGUI Support (see GUI_Function in PlayScene.cpp)

### v0.23
-----
- fixed removeChild bug

### v0.22
-----
- Updated Project to C++ 17
- added removeChild to DisplayList
- added layering to DisplayObject
- added enabling / disabling to GameObject

### v0.21
-----
- Updated to Current Version of SDL 2.0.12
- Updated to SDL Image 2.0.5
- Added SDL net 2.0.1
- removed unused dlls and libs

### V0.20 and earlier
-----------------
- Earliest SDL_Engine Build and Debug
