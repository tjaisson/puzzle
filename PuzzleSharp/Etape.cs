using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PuzzleSharp
{
    internal class Etape
    {
        public Etat etat;
        public Etape? parent;
        public Mouv mv;
        public int g;
        public int f
        {
            get { return g + etat.h; }
        }
        public Etape? NextEtape(Mouv mv)
        {
            var nEtat = etat.NextEtat(mv);
            if (nEtat == null) return null;
            return new Etape(nEtat, this, mv, g + 1);
        }

        public Etape(Etat etat, Etape? parent, Mouv mv, int g)
        {
            this.etat = etat;
            this.parent = parent;
            this.mv = mv;
            this.g = g;
        }

        public IEnumerable<Etape> History()
        {
            if (parent != null)
            {
                foreach (var e in parent.History()) yield return e;
            }
            yield return this;
        }
    }
}
