using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PuzzleSharp
{
    internal class Mapping
    {
        public const byte CV = 0xFF;
        private Dictionary<byte, char> b2c = new Dictionary<byte, char>();
        private Dictionary<char, byte> c2b = new Dictionary<char, byte>();
        public Size size;
        protected void Add(byte b, char c)
        {
            if (c == ' ') return;
            b2c.Add(b, c);
            c2b.Add(c, b);
        }
        public byte? C2B(char c)
        {
            if (c == ' ') {
                return CV;
            }
            if (c2b.TryGetValue(c, out var b))
            {
                return b;
            }
            else
            {
                return null;
            }
        }

        public char? B2C(byte b)
        {
            if (b == CV) return ' ';
            if (b2c.TryGetValue(b, out var c))
            {
                return c;
            }
            else
            {
                return null;
            }
        }

        public Mapping(IEnumerable<string> lines)
        {
            bool firstRead = false;
            int h = 0;
            int w = 0;
            byte v = 0;
            foreach (var l in lines)
            {
                int lLen = 0;
                foreach (var c in l)
                {
                    Add(v, c);
                    ++v;
                    ++lLen;
                }
                if (firstRead)
                {
                    if (w != lLen) throw new Exception("Incohérence de damier cible");
                }
                else
                {
                    firstRead = true;
                    w = lLen;
                }
                ++h;
            }
            size.Height = h;
            size.Width = w;
        }

        public byte[,] DoMap(IEnumerable<string> lines)
        {
            byte[,] items = new byte[size.Width, size.Height];
            int j = 0;
            foreach (var l in lines)
            {
                int lLen = 0;
                int i = 0;
                foreach (var c in l)
                {
                    var b = C2B(c);
                    if (!b.HasValue) throw new Exception("Incohérence de dammier de départ");
                    items[i, j] = b.Value;
                    ++lLen;
                    ++i;
                }
                if (lLen != size.Width) throw new Exception("Incohérence de dammier de départ");
                ++j;
            }
            if (j != size.Height) throw new Exception("Incohérence de dammier de départ");
            return items;
        }

        public IEnumerable<string> UnMap(byte[,] items)
        {
            for (int j = 0; j < size.Height; j++)
            {
                StringBuilder sb = new StringBuilder();
                bool done = false;
                for (int i = 0; i < size.Width; i++)
                {
                    if (done) sb.Append(' ');
                    done = true;
                    sb.Append(B2C(items[i, j]));
                }
                yield return sb.ToString();
            }
        }
    }
}
