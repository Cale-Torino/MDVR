using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace libnetclient_test
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// 
        /// Date: 2020/01/11
        ///	Author: C.A Torino
        ///	Description: Libnetclient parameter test unmanaged C++ to C#
        ///	
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());
        }
    }
}
