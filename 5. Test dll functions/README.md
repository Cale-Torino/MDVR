![Logo](https://cms.safe-tvigil.com/img/vigillogo/logosmwhite.png)

---

# Libnetclient Test

*Developed by C.A Torino, SAFE-TVIGIL*
* Links to SAFE-TVIGIL(llc) USA.
    * [Website](https://safe-tvigil.com)
    * [CMS portal](https://cms.safe-tvigil.com)
    * [ELD portal](https://eld.safe-tvigil.com)
    * [F&Q](https://tickets.safe-tvigil.com)
    

### Setup

Make sure that the correct .dll files are in the executable's directory. Below is an example of the main element of this program:

```C#
//Here the app calls methods from the C++ .dll files for use in the application.
[DllImport("libnetclient.dll", CallingConvention = CallingConvention.StdCall)]//standard call
public static extern int NETCLIENT_Initialize(int bPriorRGB16);//method called as static

//Callbacks are handled as delegates here a callback function gives us an int value.
[UnmanagedFunctionPointer(CallingConvention.StdCall)]//standard call
public delegate void FUNLoginMsgCB(int nMsg, Form1 form1);//returns int nMsg & form1 is the current form it resides on.

//A method is called like this, where NETClass is the class.cs file. variables are passed to the functions as usual
int _ini = NETClass.NETCLIENT_Initialize(0);

//Here a method is called and returns a callback delegate. FUNLoginMsgCB is the delegate function see example
FUNLoginMsgCB _callback = new FUNLoginMsgCB(FUNLoginMsgCB);
int callback = NETClass.NETCLIENT_RegLoginMsg(this, _callback);

 public static void FUNLoginMsgCB(int _nMsg, Form1 form1)
        {
            switch (_nMsg)
            {
                case 0:
                    MessageBox.Show("GPS_LOGIN_SUC");
                    break;
                case 1:
                    MessageBox.Show("GPS_LOGIN_FAILED");
                    break;
                    MessageBox.Show("DEFAULT");
                    break;
            }
        }


        /* TO DO */
        /* add 1. calling data from structs 2. add sending data via struct. */

```

**NOTE**

This app is meant to be writen in C++ as an MFC application. 
This is a conversion to C# WinForms for those clients who need to integrate into older existing applications using winforms.

* Requirements are:
    * Visual studio (2019 is preferred but you can try 2015 or 2017).
    * Windows machine (this app is for windows clients).

### Required dll's

Place the following library's in the executable's directory.

* libavdecoder.dll
* libnetclient.dll
* libnetmedia.dll
* libnetpool.dll
* libnetsbclient.dll
* libthrdpool.dll

### Development History

**C# version v1.0.0 (05-February-2020)**

Further refactoring.

* make a simplified version.

* form made smaller.
* code refactored and reduced.
* custom parameters can now be sent
* method ```FUNMCMsgCB();``` can now return proper values via IntPtrtoAnsi conversion.
* fixed garbage collection on the callbacks -- may need to take another look at a later stage.

---

**C# version v1.0.0 (12-November-2019)**

Further refactoring.

* make a simplified version.

* form made smaller.
* code refactored and reduced.
* custom parameters can now be sent
* method ```FUNMCMsgCB();``` can now return proper values via IntPtrtoAnsi conversion.
* fixed garbage collection on the callbacks -- may need to take another look at a later stage.

---

**C# version v1.0.0 (12-October-2019)**

Winform C# app required for clients using old existing systems (they want to integrate).

* first test is sucessfull application .dll's can be leveraged by the .NET framework.
* Single test form is built to display the functionality and touch base with the team.

* Design as follows:
    * log in & log out (ip,port,user,password).
    * check online.
    * device list. -- problems with reading certain attributes of the struct.
    * app info.
    * send text.
    * send ctrl.
    * read netflow -- problems with returning data.

---

**MFC version v1.0.0 (21-June-2019)**

First test run as an MFC (application runs).

* run using VS2015 MFC application is successfull.
* CMSV6 is still used since there is no need for a custom app at this time.
* App development put on hold.

---

**Initial SDK acquired (06-May-2019)**

Acquired SDK from mr Afu at [g-sky](http://www.g-sky.cn).

---

* Useful links
    * [view markdown files offline](https://stackoverflow.com/questions/9843609/view-markdown-files-offline).
    * [mastering markdown tutorial](https://guides.github.com/features/mastering-markdown/).
    * [markdown to pdf](https://www.markdowntopdf.com/).