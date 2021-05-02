using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Timers;
using System.Windows.Forms;
using System.Windows.Threading;
using static PicfileExtract_Panel.LoggerClass;
using Timer = System.Timers.Timer;

namespace PicfileExtract_Panel
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Logger.WriteLine(" ***About Clicked*** ");
            Form2 f2 = new Form2();
            f2.ShowDialog();
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //exit
            Logger.WriteLine(" ***Exit Clicked*** ");
            Reallyexit();
        }

        private void fontToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //font
            Logger.WriteLine(" ***Font Box Clicked*** ");
            if (fontDialog1.ShowDialog() == DialogResult.OK)
            {
                richTextBox1.Font = richTextBox1.Font = new Font(fontDialog1.Font, fontDialog1.Font.Style);
                richTextBox1.ForeColor = fontDialog1.Color;
            }
        }

        string path = "";
        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //save
            Logger.WriteLine(" ***Save Clicked*** ");
            if (path != "")
            {
                File.WriteAllText(path, richTextBox1.Text);
            }
            else
            {
                saveAsToolStripMenuItem_Click(sender, e);
            }
        }

        private void saveAsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //save as
            Logger.WriteLine(" ***Save As Clicked*** ");
            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                File.WriteAllText(path = saveFileDialog1.FileName, richTextBox1.Text);
            }
        }
        private void Reallyexit()
        {
            //exit YES/NO
            string _text = "Do you really want to exit the application?";
            string _caption = "Exit Application?";
            var selectedOption = MessageBox.Show(_text, _caption, MessageBoxButtons.YesNo, MessageBoxIcon.Question);
            if (selectedOption == DialogResult.Yes)
            {
                try
                {
                    Environment.Exit(1);
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.ToString(), "Exit Error", MessageBoxButtons.YesNo, MessageBoxIcon.Question);
                    return;
                }

            }
            else if (selectedOption == DialogResult.No)
            {
                //Do nothing
            }
        }

        private void CreateFolder()
        {
            try
            {
                //CreatFolder
                string path = Application.StartupPath;
                Directory.CreateDirectory(path + "\\Logs");
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString(), "Create Folder Error!", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            //load
            CreateFolder();
            myTimer = new Timer();
            myTimer.Enabled = false;
            timer2 = new DispatcherTimer();
            timer2.IsEnabled = false;
            numericUpDown1.Text = "5";
            if (Properties.Settings.Default.looptime != string.Empty)
            {
                numericUpDown1.Text = Properties.Settings.Default.looptime;
            }
            richTextBox1.AppendText("[" + DateTime.Now + "] ***- APPLICATION STARTED -*** " + Environment.NewLine);
            Logger.WriteLine(" ***- APPLICATION STARTED -*** ");
            toolStripStatusLabel1.Text = "Ready";
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            //exit YES/NO
            Logger.WriteLine(" ***Exit Form Closing Clicked*** ");
            string _text = "Do you really want to exit the application?";
            string _caption = "Exit Application?";
            var selectedOption = MessageBox.Show(_text, _caption, MessageBoxButtons.YesNo, MessageBoxIcon.Question);
            if (selectedOption == DialogResult.Yes)
            {
                Logger.WriteLine(" ***Exiting Form...X *** ");
                //don't need to call Application.Exit(); because the form is already closing
            }
            else if (selectedOption == DialogResult.No)
            {
                //cancle closing
                Logger.WriteLine(" ***Cancel Exiting Form...X *** ");
                e.Cancel = true;
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            //run once
            Logger.WriteLine(" ***Run Once Start*** ");
            richTextBox1.AppendText("["+ DateTime.Now+"] ***Run Once Start*** " +Environment.NewLine);
            checks();
            if (!backgroundWorker1.IsBusy)
            {
                backgroundWorker1.RunWorkerAsync();
            }
        }
        private void checks()
        {
            //checks
            if (myTimer.Enabled)
            {
                myTimer.Stop();
            }
            if (timer2.IsEnabled)
            {
                timer2.Stop();
            }
        }
        private Timer myTimer;
        private void timer(int ctime)
        {
            //timer
            myTimer = new Timer();
            myTimer.Elapsed += new ElapsedEventHandler(DisplayTimeEvent);
            myTimer.Interval = ctime; // 1000 ms is one second
            myTimer.Start();
        }

        public void DisplayTimeEvent(object source, ElapsedEventArgs e)
        {
            // code here will run every x second
            backgroundWorker1.RunWorkerAsync();
            loopRun(ConvertMinutesToseconds(Convert.ToInt32(numericUpDown1.Text)));
        }
        private void button2_Click(object sender, EventArgs e)
        {
            //run loop
            Logger.WriteLine(" ***Run Loop Start*** ");
            richTextBox1.AppendText("[" + DateTime.Now + "] ***Run Loop Start*** " + Environment.NewLine);
            int i = Convert.ToInt32(numericUpDown1.Text);
            int ctime = ConvertMinutesToMilliseconds(i);
            checks();
            loopRun(ConvertMinutesToseconds(Convert.ToInt32(numericUpDown1.Text)));
            if (!backgroundWorker1.IsBusy)
            {
                timer(ctime);
            }            
        }

        private static int ConvertMinutesToseconds(int minutes)
        {
            return (int)TimeSpan.FromMinutes(minutes).TotalSeconds;
        }
        private static int ConvertMinutesToMilliseconds(int minutes)
        {
            return (int)TimeSpan.FromMinutes(minutes).TotalMilliseconds;
        }

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

        private int counter;
        DispatcherTimer timer2;
        private void loopRun(int count)
        {
            //time to next loop run
            timer2 = new DispatcherTimer();
            counter = count;
            timer2.Interval = new TimeSpan(0, 0, 0, 1);
            timer2.Tick += new EventHandler(timer1_Tick);
            timer2.Start();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            toolStripStatusLabel1.Text = counter + " Seconds Remaining";
            if (counter > 0)
            {
                counter--;
            }
            else
            {
                //toolStripStatusLabel1.Text = "Times Up";
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            Logger.WriteLine(" ***Stop Loop*** ");
            richTextBox1.AppendText("[" + DateTime.Now + "] ***Stop Loop*** " + Environment.NewLine);
            timer2.Stop();
        }

        private void copyToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Logger.WriteLine(" ***Copy Selected Clicked*** ");
            Clipboard.Clear();
            try
            {
                Clipboard.SetText(richTextBox1.SelectedText);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "No Text Selected", MessageBoxButtons.OK, MessageBoxIcon.Information);
                return;
            }
        }

        private void copyAllToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Logger.WriteLine(" ***Copy All Clicked*** ");
            Clipboard.Clear();
            richTextBox1.SelectAll();
            richTextBox1.Copy();
        }

        private void clearToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Logger.WriteLine(" ***Clear All Clicked*** ");
            Clipboard.Clear();
            richTextBox1.SelectAll();
            richTextBox1.Clear();
        }

        private void cutAllToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Logger.WriteLine(" ***Cut All Clicked*** ");
            Clipboard.Clear();
            richTextBox1.SelectAll();
            richTextBox1.Copy();
            richTextBox1.Clear();
        }
    }
}
