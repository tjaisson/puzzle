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
        protected Mapping map;
        public byte[,] items;
        public int h;
        public Point cv;

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
            for (int i = 0; i < map.size.Width; ++i)
                for (int j = 0; j < map.size.Height; ++j)
                    if (items[i, j] != other.items[i, j]) return false;
            return true;
        }

        public Etat(Mapping map, byte[,] items, Point cv, int h)
        {
            this.map = map;
            this.items = items;
            this.cv = cv;
            this.h = h;
        }

        public Etat(Mapping map, IEnumerable<string> lines)
        {
            this.map = map;
            var items = map.DoMap(lines);
            this.items = items;
            Point? nCv = null;
            int nH = 0;
            for (int i = 0; i < map.size.Width; ++i)
                for (int j = 0; j < map.size.Height; ++j)
                {
                    if (items[i, j] == Mapping.CV)
                    {
                        nCv = new Point(i, j);
                    }
                    else
                    {
                        nH += Math.Abs((items[i, j] % map.size.Width) - i);
                        nH += Math.Abs((items[i, j] / map.size.Width) - j);
                    }
                }
            if (!nCv.HasValue) throw new Exception("Case vide non trouvée.");
            this.cv = nCv.Value;
            this.h = nH;
        }

        public Etat? NextEtat(Mouv mv)
        {
            var nCv = NextCv(cv, mv);
            if (!nCv.HasValue) return null;
            Point nCvV = nCv.Value;
            var nItems = (byte[,])items.Clone();
            byte v = items[nCvV.X, nCvV.Y];
            nItems[cv.X, cv.Y] = v;
            nItems[nCvV.X, nCvV.Y] = Mapping.CV;
            int nH = h + Gain(v, cv, mv);
            return new Etat(map, nItems, nCvV, nH);
        }

        protected Point? NextCv(Point p, Mouv mv)
        {
            switch (mv)
            {
                case Mouv.NORD:
                    if(p.Y <= 0) return null;
                    return new Point(p.X, p.Y - 1);
                case Mouv.EST:
                    var nx = p.X + 1;
                    if (nx >= map.size.Width) return null;
                    return new Point(nx, p.Y);
                case Mouv.SUD:
                    var ny = p.Y + 1;
                    if (ny >= map.size.Height) return null;
                    return new Point(p.X, ny);
                case Mouv.OUEST:
                    if (p.X <= 0) return null;
                    return new Point(p.X - 1, p.Y);
                default: return null;
            }

        }

        protected int Gain(byte v, Point p, Mouv mv)
        {
            switch (mv)
            {
                case Mouv.NORD:
                    if (v / map.size.Width >= p.Y) return -1;
                    return 1;
                case Mouv.EST:
                    if (v % map.size.Width <= p.X) return -1;
                    return 1;
                case Mouv.SUD:
                    if (v / map.size.Width <= p.Y) return -1;
                    return 1;
                case Mouv.OUEST:
                    if (v % map.size.Width >= p.X) return -1;
                    return 1;
            }
            return 0;
        }
    }
}
