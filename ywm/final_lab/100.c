#include <stdio.h>

#define loop_min -100
#define loop_max 100
#define in_range(x) (x>loop_min && x<loop_max)

int main()
{
    int va, vb, vc, vd, ve, vf, vg, vh;
    for (va = loop_min; va < loop_max; va++) {
        vb = 13 - va;
        if (!in_range(vb)) continue;
        
        for (ve = loop_min; ve < loop_max; ve++) {
            vh = 5 - ve;
            if (!in_range(vh)) continue;

            for (vc = loop_min; vc < loop_max; vc++) {
                if (ve==0 && vc!=4) continue;
                else if (ve==0 && vc==4) ;
                else {
                    if ((vc-4)%ve != 0) continue;
                    vd = (vc - 4) / ve;
                }
                if (!in_range(vd)) continue;
                if (va==4 && vc!=0) continue;
                else if (va==4 && vc==0) ;
                else {
                    if (vc%(4-va) != 0) continue;
                    vf = vc / (4 - va);
                    if (vf == 0) continue;
                }
                if (!in_range(vf)) continue;
                vg = 4 + vh - vf;
                if (!in_range(vg)) continue;
                if (!(vb-vd*vg == 4)) continue;

                printf("%d %d %d %d %d %d %d %d\n", 
                        va, vb, vc, vd, ve, vf, vg, vh);
            }
        }
    }

    return 0;
}