using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ColorList
{
    public static class Util
    {
        public static string toHexStr(byte value)
        {
            return BitConverter.ToString(new byte[] { value });
        }
        public static string toHexStr(int value)
        {
            string r = toHexStr((byte)((value >> 24) & 0x0FF));
            r += toHexStr((byte)((value >> 16) & 0x0FF));
            r += toHexStr((byte)((value >> 8) & 0x0FF));
            r += toHexStr((byte)(value & 0x0FF));
            return r;
        }

        public static string colorToCssStr(Color col)
        {
            string r = "#";
            int value = col.ToArgb();
            r += toHexStr((byte)((value >> 16) & 0x0FF));
            r += toHexStr((byte)((value >> 8) & 0x0FF));
            r += toHexStr((byte)(value & 0x0FF));
            return r;
        }
        public static string colorToArgbStr(Color col)
        {
            string r = toHexStr(col.ToArgb());
            return r;
        }

        public static string omwColorCtorArg(ColCont cc)
        {
            string str;

            if (cc.color.A == 0xFF) str = "argb_" + cc.name_c;
            else if (cc.name == "Transparent") str = "255, 255, 255, 0";
            else str = "TODO";

            return str;
        }
    }

    public class ColCont
    {
        public Color color;
        public int argb;
        public string name;
        public string name_c;
        public string value_c;
        public string value_css;

        public ColCont(KnownColor kc)
        {
            color = Color.FromKnownColor(kc);
            argb = color.ToArgb();
            name = kc.ToString();
            value_c = "0x" + Util.colorToArgbStr(color);
            value_css = Util.colorToCssStr(color);

            name_c = name;
            char firstChar = name_c[0];
            if ((firstChar >= 'A') && (firstChar <= 'Z'))
            {
                name_c = name_c.Remove(0, 1).Insert(0, new string((char)(firstChar + 32), 1));
            }
        }
    }

    public partial class mainForm : Form
    {
        private ColCont[] webColors;
        private ColCont[] sysColors;

        public mainForm()
        {
            InitializeComponent();
            this.StartPosition = FormStartPosition.CenterScreen;
            this.Size = new Size(600, 700);
            this.MinimumSize = new Size(600, 700);
            this.Text = "Color List";
            this.FormClosing += new FormClosingEventHandler(this.mainForm_closing);



            KnownColor[] kc_colors = Enum.GetValues(typeof(KnownColor)).Cast<KnownColor>().ToArray();

            // https://docs.microsoft.com/en-us/dotnet/api/system.drawing.systemcolors?view=net-5.0
            KnownColor[] kc_sysColors = new KnownColor[]
            {
                KnownColor.ActiveBorder,
                KnownColor.ActiveCaption,
                KnownColor.ActiveCaptionText,
                KnownColor.AppWorkspace,
                KnownColor.ButtonFace,
                KnownColor.ButtonHighlight,
                KnownColor.ButtonShadow,
                KnownColor.Control,
                KnownColor.ControlDark,
                KnownColor.ControlDarkDark,
                KnownColor.ControlLight,
                KnownColor.ControlLightLight,
                KnownColor.ControlText,
                KnownColor.Desktop,
                KnownColor.GradientActiveCaption,
                KnownColor.GradientInactiveCaption,
                KnownColor.GrayText,
                KnownColor.Highlight,
                KnownColor.HighlightText,
                KnownColor.HotTrack,
                KnownColor.InactiveBorder,
                KnownColor.InactiveCaption,
                KnownColor.InactiveCaptionText,
                KnownColor.Info,
                KnownColor.InfoText,
                KnownColor.Menu,
                KnownColor.MenuBar,
                KnownColor.MenuHighlight,
                KnownColor.MenuText,
                KnownColor.ScrollBar,
                KnownColor.Window,
                KnownColor.WindowFrame,
                KnownColor.WindowText
            };

            List<ColCont> tmp_webColors = new List<ColCont>();
            for (int i = 0; i < kc_colors.Length; ++i)
            {
                KnownColor kc = kc_colors[i];
                if (!kc_sysColors.Contains<KnownColor>(kc)) tmp_webColors.Add(new ColCont(kc));
            }
            webColors = tmp_webColors.ToArray();

            sysColors = new ColCont[kc_sysColors.Length];
            for (int i = 0; i < kc_sysColors.Length; ++i)
            {
                sysColors[i] = new ColCont(kc_sysColors[i]);
            }



            int posX = 3;
            int posY = 3;
            createColorListControls(new Point(posX, posY), "Web Colors", webColors);
            posX = 300;
            posY = createColorListControls(new Point(posX, posY), "System Colors", sysColors);

            posX += 20;
            posY += 50;

            Button btn_info = new Button();
            btn_info.Text = "info";
            btn_info.Size = new Size(75, 35);
            btn_info.Location = new Point(posX, posY);
            btn_info.Click += new EventHandler(this.btn_info_click);
            this.Controls.Add(btn_info);
            posY += btn_info.Size.Height;

            this.Invalidate();
        }

        private int createColorListControls(Point position, string title, ColCont[] colors)
        {
            Font tmpFont;
            const int margin = 3;
            int posX = position.X;
            int posY = margin;

            Label label_title = new Label();
            label_title.AutoSize = true;
            label_title.Text = title;
            tmpFont = label_title.Font;
            label_title.Font = new Font(tmpFont.FontFamily, 12, tmpFont.Style, tmpFont.Unit);
            label_title.Location = new Point(posX, posY);
            this.Controls.Add(label_title);
            posY += label_title.Size.Height;

            posY += 5;

            for (int i = 0; i < colors.Length; ++i)
            {
                PictureBox pbx = new PictureBox();
                pbx.BackColor = colors[i].color;
                pbx.BorderStyle = BorderStyle.FixedSingle;
                pbx.Size = new Size(50, 23);
                pbx.Location = new Point(posX, posY);
                this.Controls.Add(pbx);

                TextBox tbx_value = new TextBox();
                tbx_value.Text = colors[i].value_css;
                //tbx_value.BorderStyle = BorderStyle.None;
                tbx_value.ReadOnly = true;
                tbx_value.Size = new Size(55, 23);
                tbx_value.Location = new Point(pbx.Location.X + pbx.Size.Width + margin * 2, posY);
                this.Controls.Add(tbx_value);

                TextBox tbx_name = new TextBox();
                tbx_name.Text = colors[i].name;
                //tbx_name.BorderStyle = BorderStyle.None;
                tbx_name.ReadOnly = true;
                tbx_name.Size = new Size(140, 23);
                tbx_name.Location = new Point(tbx_value.Location.X + tbx_value.Size.Width + margin * 2, posY);
                this.Controls.Add(tbx_name);



                posY += pbx.Size.Height;
                posY += margin;
            }

            PictureBox pbx_spacer = new PictureBox();
            pbx_spacer.Size = new Size(50, 0);
            pbx_spacer.Location = new Point(posX, posY);
            this.Controls.Add(pbx_spacer);
            posY += pbx_spacer.Size.Height;

            return posY;
        }

        private void mainForm_Load(object sender, EventArgs e)
        {
            config = loadConfig();
            this.Location = config.winPos;
            this.Size = config.winSize;

            if (config.createOutputFiles)
            {
                string cppStr = "namespace colors\n{\n";
                for (int i = 0; i < webColors.Length; ++i) cppStr += "constexpr int32_t argb_" + webColors[i].name_c + " = " + webColors[i].value_c + ";\n";
                cppStr += "\n";
                for (int i = 0; i < webColors.Length; ++i) cppStr += "const omw::Color " + webColors[i].name_c + " = omw::Color(" + Util.omwColorCtorArg(webColors[i]) + ");\n";
                cppStr += "\n";
                cppStr += "namespace windows\n{\n";
                for (int i = 0; i < sysColors.Length; ++i) cppStr += "    constexpr int32_t argb_" + sysColors[i].name_c + " = " + sysColors[i].value_c + ";\n";
                cppStr += "    \n";
                for (int i = 0; i < sysColors.Length; ++i) cppStr += "    const omw::Color " + sysColors[i].name_c + " = omw::Color(" + Util.omwColorCtorArg(sysColors[i]) + ");\n";
                cppStr += "}\n";
                cppStr += "}\n";
                System.IO.File.WriteAllBytes("omw_colors.cpp", Encoding.UTF8.GetBytes(cppStr));


                string csvStr = "Color,Name\n";
                for (int i = 0; i < sysColors.Length; ++i) csvStr += sysColors[i].value_css + "," + sysColors[i].name + "\n";
                System.IO.File.WriteAllBytes("windowsSystemColors.csv", Encoding.UTF8.GetBytes(csvStr));
            }
        }
        private void mainForm_closing(object sender, FormClosingEventArgs e)
        {
            config.createOutputFiles = false;
            config.winPos = this.Location;
            config.winSize = this.Size;
            saveConfig(config);
        }

        private void btn_info_click(object sender, EventArgs e)
        {
            const string url = "https://github.com/oblaser/omw/tree/master/tools/colorList/ColorList";

            System.Diagnostics.ProcessStartInfo psi = new System.Diagnostics.ProcessStartInfo("cmd", "/c start " + url);
            psi.CreateNoWindow = true;
            System.Diagnostics.Process.Start(psi);
        }



        private struct Config
        {
            public bool createOutputFiles;
            public Point winPos;
            public Size winSize;
        }

        private Config config;
        private static readonly string configFile = "config.cfg";

        private Config loadConfig()
        {
            Config cfg;

            try
            {
                string[] lines = Encoding.UTF8.GetString(System.IO.File.ReadAllBytes(configFile)).Split('\n');

                cfg.createOutputFiles = (Convert.ToInt32(lines[0].Split(' ')[0]) != 0);

                int x = Convert.ToInt32(lines[1].Split(' ')[0]);
                int y = Convert.ToInt32(lines[2].Split(' ')[0]);
                int w = Convert.ToInt32(lines[3].Split(' ')[0]);
                int h = Convert.ToInt32(lines[4].Split(' ')[0]);

                cfg.winPos = new Point(x, y);
                cfg.winSize = new Size(w, h);
            }
            catch
            {
                cfg.createOutputFiles = true;
                cfg.winPos = this.Location;
                cfg.winSize = this.Size;
            }

            return cfg;
        }
        private void saveConfig(Config cfg)
        {
            const int tab = 20;
            string str = "";
            string line;

            line = (cfg.createOutputFiles ? "1" : "0");
            while (line.Length < tab) line += " ";
            line += "# createOutputFiles";
            str += line + "\n";

            if (this.WindowState != FormWindowState.Normal) cfg = loadConfig();

            line = cfg.winPos.X.ToString();
            while (line.Length < tab) line += " ";
            line += "# winPos.X";
            str += line + "\n";

            line = cfg.winPos.Y.ToString();
            while (line.Length < tab) line += " ";
            line += "# winPos.Y";
            str += line + "\n";

            line = cfg.winSize.Width.ToString();
            while (line.Length < tab) line += " ";
            line += "# winSize.Width";
            str += line + "\n";

            line = cfg.winSize.Height.ToString();
            while (line.Length < tab) line += " ";
            line += "# winSize.Height";
            str += line + "\n";

            try
            {
                System.IO.File.WriteAllBytes(configFile, Encoding.UTF8.GetBytes(str));
            }
            catch { }
        }
    }
}
