![Logo](https://cms.safe-tvigil.com/img/vigillogo/logosmwhite.png)

---

# PicfileExtract_Panel (SAFE-TVIGIL Device Manager)

*Developed by C.A Torino, SAFE-TVIGIL*
* Links to SAFE-TVIGIL(llc) USA.
    * [Website](https://safe-tvigil.com)
    * [CMS portal](https://cms.safe-tvigil.com)
    * [ELD portal](https://eld.safe-tvigil.com)
    * [F&Q](https://tickets.safe-tvigil.com)
    

### Setup

This program is written in C# WinForms using .Net Framework 4.7.2.

This Application was made to control the ```IndexPicfileExtract.exe```.

The control panel controls the times at which ```IndexPicfileExtract.exe``` will run and if it will run in a loop every ```X``` H:M:S .

```
//The main event runs as a async background task.
private void backgroundWorker1_DoWork(object sender, DoWorkEventArgs e)
{
    try
    {
        Invoke((MethodInvoker)(() => toolStripProgressBar1.Value = 50));
        Invoke((MethodInvoker)(() => toolStripStatusLabel1.Text = "Working..."));
        Invoke(new MethodInvoker(() => Classes.RunExeClass.RunExeActions()));
    }
    catch (Exception ex)
    {
        MessageBox.Show(ex.ToString(), "Create Folder Error!", MessageBoxButtons.OK, MessageBoxIcon.Error);
        return;
    }
    Invoke((MethodInvoker)(() => Logger.WriteLine(" ***Run End, Check Time*** ")));
    Invoke((MethodInvoker)(() => richTextBox1.AppendText("[" + DateTime.Now + "] ***Run End*** " + Environment.NewLine)));
    Invoke((MethodInvoker)(() => toolStripProgressBar1.Value = 100));
    Invoke((MethodInvoker)(() => toolStripStatusLabel1.Text = "Completed Time: " + DateTime.Now));
}


//RunExeClass runs the exe.
class RunExeClass
{
    public static void RunExeActions()
    {
        string pathToFile = Application.StartupPath + "\\IndexPicfileExtract.exe";
        Process runProg = new Process();
        try
        {
            runProg.StartInfo.FileName = pathToFile;
            runProg.StartInfo.CreateNoWindow = true;
            runProg.Start();
            runProg.WaitForExit();
        }
        catch (Exception ex)
        {
            MessageBox.Show(ex.ToString(), "Could Not Run: IndexPicfileExtract.exe", MessageBoxButtons.OK, MessageBoxIcon.Error);
            return;
        }
    }
}

```

**NOTE**

* Requirements are:
    * Visual studio (2019 is preferred but you can try 2015 or 2017).
    * Windows machine (this app is for windows clients).
    * App runs on Windows Server 2012.

### Required Framework's

This application only requires Microsofts .Net Framework 4.7.2.

### Development History

**Version v1.0.0 (14-May-2020)**

Small improvments

* form MinimumSize set to 460,367 to prevent over minimize.
* contextMenuStrip added for richtextbox.
* copy selected, cody all, clear all, cut all contextMenuStrip items added.

Bugs

* fixed right click copy selected bug where app would crash if no text was selected.

---

**Initial Version v1.0.0 (13-May-2020)**
C# Winform app to control the ```IndexPicfileExtract.exe``` executable on the server.

* Design as follows:
    * **menuStrip** containing: *file*, *about box*, *font*, *exit*.
    * under *file* in the **menuStrip**: *save*, *save as*.
    * under *file* - *save*, *save as*: **savefileDialog** is used.
    * under *font* in the **menuStrip**: **fontDialog** is used.
    * controls **groupBox** containing: *run once button*, *run loop button*, *stop loop button* and *minute numericallupdown box*.
    * memo **groupBox** containing: *richtextbox* to display event data.
    * **statusStrip** to show the progress of ongoing events.

---

* Useful links
    * [view markdown files offline](https://stackoverflow.com/questions/9843609/view-markdown-files-offline).
    * [mastering markdown tutorial](https://guides.github.com/features/mastering-markdown/).
    * [markdown to pdf](https://www.markdowntopdf.com/).