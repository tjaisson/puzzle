using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PuzzleSharp
{
    internal class Etat: IEquatable<Etat>
    {
        protected static bool sized = false;
        protected static int width, height;
        protected byte[,] items;
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

        public Etat()
        {
            if (! sized) throw new Exception("Dimensions pas initialisées.");
            items = new byte[width, height];
        }
    }
}
