using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PuzzleSharp
{
    internal class Etat: IEquatable<Etat>
    {
        const byte CV = 0xFF;
        protected static bool sized = false;
        protected static int width, height;
        protected byte[,] items;
        protected int h;
        protected Point cv;
        public static void set_size(int w, int h) {
            if (sized) throw new Exception("Dimensions déjà initialisées.");
            width = w;
            height = h;
            sized = true;
        }

        public override bool Equals(object? obj)
        {
            if (obj == null)
                return false;

            Etat? e = obj as Etat;
            if (e == null)
                return false;
            else
                return Equals(e);
        }
        public override int GetHashCode()
        {
            byte[] parts = new byte[4];
            int i = 0;
            foreach (var item in items)
            {
                parts[i] ^= item;
                i = (i >= 3) ? 0 : i + 1;
            }
            return parts[0] | (parts[1] << 8) | (parts[2] << 16) | (parts[3] << 24);
        }
        public bool Equals(Etat? other)
        {
            if (other == null)
                return false;
            for (int i = 0; i < width; ++i)
                for (int j = 0; j < height; ++j)
                    if (items[i, j] != other.items[i, j]) return false;
            return true;
        }

        public Etat(byte[,] items, Point cv, int h)
        {
            //if (! sized) throw new Exception("Dimensions pas initialisées.");
            this.items = items;
            this.cv = cv;
            this.h = h;
        }

        public Etat? NextEtat(Mouv mv)
        {
            var nCv = NextCv(cv, mv);
            if (!nCv.HasValue) return null;
            Point nCvV = nCv.Value;
            var nItems = (byte[,])items.Clone();
            byte v = items[nCvV.X, nCvV.Y];
            nItems[cv.X, cv.Y] = v;
            nItems[nCvV.X, nCvV.Y] = CV;
            int nH = h + Gain(v, cv, mv);
            return new Etat(nItems, nCvV, nH);
        }

        protected static Point? NextCv(Point p, Mouv mv)
        {
            switch (mv)
            {
                case Mouv.NORD:
                    if(p.Y <= 0) return null;
                    return new Point(p.X, p.Y - 1);
                case Mouv.EST:
                    if (p.X >= width) return null;
                    return new Point(p.X + 1, p.Y);
                case Mouv.SUD:
                    if (p.Y >= height) return null;
                    return new Point(p.X, p.Y + 1);
                case Mouv.OUEST:
                    if (p.X <= 0) return null;
                    return new Point(p.X - 1, p.Y);
                default: return null;
            }

        }

        protected static int Gain(Byte v, Point p, Mouv mv)
        {
            switch (mv)
            {
                case Mouv.NORD:
                    if (v / width >= p.X) return -1;
                    return 1;
                case Mouv.EST:
                    if (v % width <= p.Y) return -1;
                    return 1;
                case Mouv.SUD:
                    if (v / width <= p.X) return -1;
                    return 1;
                case Mouv.OUEST:
                    if (v % width >= p.Y) return -1;
                    return 1;
            }
            return 0;
        }
    }
}
