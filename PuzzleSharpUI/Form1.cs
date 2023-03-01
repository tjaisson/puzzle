using PuzzleSharp;

namespace PuzzleSharpUI
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private Puzzle? pz = null;

        private async void button1_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() != DialogResult.OK) return;
            var lines = File.ReadAllLines(openFileDialog1.FileName);
            Puzzle pz = Puzzle.Create(lines);
            this.pz = pz;
            timer1.Tick += timer_Tick;
            timer1.Start();
            Etape? sol = null;
            await Task.Run(() =>
            {
                sol = pz.Solve();
            });
            timer1.Stop();
            this.pz = null;
            if (sol == null) {
                TB1.AppendText("pas de solution");
                return;
            }
            int i = 1;
            foreach (var etape in sol.History())
            {
                if (etape.mv != Mouv.RIEN) TB1.AppendText($"\r\n{i++} : {etape.mv}\r\n");
                foreach (var line in pz.map.UnMap(etape.etat.items))
                {
                    TB1.AppendText(line + Environment.NewLine);
                }
            }

        }
        private void timer_Tick(object sender, EventArgs e)
        {
            Puzzle cpz = pz;
            if (cpz == null) return;
            TB2.AppendText($"MinH: {cpz.MinH}\r\n");
            TB2.AppendText($"Vus: {cpz.vus}\r\n");
            Etape cEtape = cpz.CurrentEtape;
            TB2.AppendText($"Current: {cEtape.etat.h}\r\n\r\n");
        }
    }
}