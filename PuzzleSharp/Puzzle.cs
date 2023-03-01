using System;
using System.Collections;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PuzzleSharp
{
    internal class Puzzle
    {
        public Mapping map;
        public HashSet<Etat> etatsVus;
        public PriorityQueue<Etape, Etape> LEAE;
        public Size size
        {
            get { return map.size; }
        }

        public static Puzzle Create(IEnumerable<string> lines)
        {
            Queue<string> cible= new Queue<string>();
            Queue<string> depart = new Queue<string>();
            bool done = false;
            foreach(var l in lines)
            {
                if (done)
                {
                    depart.Enqueue(l);
                }
                else if (l == "") {
                    done = true;
                }
                else
                {
                    cible.Enqueue(l);
                }
            }
            Mapping map = new Mapping(cible);
            Puzzle pz = new Puzzle(map);
            Etat etat = new Etat(map, depart);
            Etape etape = new Etape(etat, null, Mouv.RIEN, 0);
            pz.PushInLEAE(etape);
            pz.CurrentEtape = etape;
            pz.MinH = etat.h;
            return pz;
        }

        Puzzle(Mapping map)
        {
            this.map = map;
            etatsVus = new HashSet<Etat>();
            LEAE = new PriorityQueue<Etape, Etape>(Comparer<Etape>.Create(
                (x, y) =>
                {
                    var d = x.etat.h - y.etat.h;
                    if (d != 0) return d;
                    return x.g - y.g;
                }
                ));
        }

        public void PushInLEAE(Etape etape)
        {
            LEAE.Enqueue(etape, etape);
        }

        public bool TryPopLEAE(out Etape etape)
        {
            return LEAE.TryDequeue(out etape, out var p);
        }

        public int MinH;
        public Etape CurrentEtape;
        public int vus = 0;
        public Etape? Solve()
        {
            while(TryPopLEAE(out var etape))
            {
                CurrentEtape = etape;
                if (etape.etat.h == 0) return etape;
                foreach (var mv in etape.mv.Nexts())
                {
                    var nEtape = etape.NextEtape(mv);
                    if ((nEtape != null) && etatsVus.Add(nEtape.etat))
                    {
                        vus = etatsVus.Count;
                        if (nEtape.etat.h < MinH) MinH = nEtape.etat.h;
                        PushInLEAE(nEtape);
                    }
                }
            }
            return null;
        }
    }
}
