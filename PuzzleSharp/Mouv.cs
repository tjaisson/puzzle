﻿namespace PuzzleSharp
{
    internal enum Mouv
    {
        NORD = 0,
        EST = 1,
        SUD = 2,
        OUEST = 3,
        RIEN
    }
    internal static class Mouvs
    {
        public static IEnumerator<Mouv> Nexts(this Mouv m)
        {
            var op = m.Oposite();
            foreach(var nm in All())
            {
                if (nm != op) yield return nm;
            }
        }

        public static Mouv Oposite(this Mouv m)
        {
            switch (m)
            {
                case Mouv.NORD: return Mouv.SUD;
                case Mouv.EST: return Mouv.OUEST;
                case Mouv.SUD: return Mouv.NORD;
                case Mouv.OUEST: return Mouv.EST;
                default: return Mouv.RIEN;
            }
        }

        private static IEnumerable<Mouv> All()
        {
            yield return Mouv.NORD;
            yield return Mouv.EST;
            yield return Mouv.SUD;
            yield return Mouv.OUEST;
        }
    }
}
