# Password_Vault
Making a password vault to store all my passwords and directly inject them when needed using an esp32 s3

I will be using an esp32 s3 and a tft (240 x 320) screen. the controller will store all my passwords and the screen will act as a viewport, 2 push buttons will also be used to navigate and select the name of the site e.g. GitHub, then an option will pop up saying something like inject or similar. 
The controller will be programmed as a keyboard that can be connectd to the device via Bluetooth, therefore i will be using a library that supports keyboard Bluetooth such as HijelBLEKeyboard. 

Firstly i have coded a small programme (file name: inject_password_1) that stores only 1 password, only using the microcontroller's built in features and boot button, the programme works by simply connecting the controller to a device e.g. a laptop, phone or a TV, then approach the point where it asks for the exact password stored in the controller, hit the boot button on the esp32 s3 and it automatically fills it in.
**Stage BUG and fix**
If the password includes (@) the code will treat it as (") this is because my laptop expects UK keyboard layout and the language expects US layout
FIX: using \" (shift + 2), ie: Password@1 will be ("Password\"1")


