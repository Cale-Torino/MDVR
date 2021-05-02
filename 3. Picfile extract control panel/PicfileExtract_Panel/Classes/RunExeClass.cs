using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace PicfileExtract_Panel.Classes
{
    class RunExeClass
    {
        public static void RunExeActions()
        {
            //CMSv6_Picture_Extract.exe
            //IndexPicfileExtract.exe
            string pathToFile = Application.StartupPath + "\\CMSv6_Picture_Extract.exe";
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
                MessageBox.Show(ex.ToString(), "Could Not Run: CMSv6_Picture_Extract.exe", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
        }
    }
}
