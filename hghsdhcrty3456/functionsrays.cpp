


            struct float2
            {
                float x;
                float y;
            };

            struct float3
            {
                float x;
                float y;
                float z;
            };

            struct float4
            {
                float x;
                float y;
                float z;
                float w;
            };

            struct float4col
            {
                float r;
                float g;
                float b;
                float a;
                COLORREF rgb;
                void InicializeStruct(){rgb = RGB(r,g,b);}
                /*
                float GetRed()   return r;
                float GetGreen() return g;
                float GetBlue()  return b;
                float GetAlpha() return a;
                */
                float GetRGB()
                {
                    return rgb;
                }

            };



float length(float2 v){
    return v.x*v.x + v.y*v.y;
}

/*
            float _FrustumCornersES[4][4;
            uniform sampler2D _MainTex;
            uniform float4 _MainTex_TexelSize;
            uniform float4x4 _CameraInvViewMatrix;
            uniform float3 _CameraWS;

            uniform float _Param;
            uniform float3 _Object1;
            uniform float3 _Object2;
*/
            static const float MAX_DIST = 50;
            static const int ITERATIONS = 500;

            float smin(float a, float b, float k)
            {
                float h = clamp(0.5 + 0.5 * (b - a) / k, 0.0, 1.0);
                return lerp(b, a, h) - k * h * (1.0 - h);
            }

            float plane(float3 p)
            {
                return p.y;
            }

            float sphere(float4 s, float3 p)
            {
                return length(p - s.xyz) - s.w;
            }

            float cube(float4 s, float3 p)
            {
                float3 q = abs(p - s.xyz) - s.w;
                return length(max(q, 0)) + min(max(q.x, max(q.y, q.z)), 0);
            }

            float getDist(float3 p)
            {
                float dist1 = sphere(float4(_Object1, 1), p);
                float dist2 = cube(float4(_Object2, 0.75), p);
                float dist3 = plane(p);
                return smin(smin(dist1, dist2, 0.5), dist3, 0.5);
            }

            float getNormal(float3 p)
            {
                float d = getDist(p);
                float2 e = {0.001, 0};
                float3 n = d - (getDist(p - e.xyy), getDist(p - e.yxy), getDist(p - e.yyx));
                return normalize(n);
            }

            float raymarchLight(float3 ro, float3 rd)
            {
                float dO = 0;
                float md = 1;
                for (int i = 0; i < 20; i++)
                {
                    float3 p = ro + rd * dO;
                    float dS = getDist(p);
                    md = min(md, dS);
                    dO += dS;
                    if(dO > 50 || dS < 0.1) break;
                }
                return md;
            }
/*
            float getLight(float3 p, float3 ro, int i, float3 lightPos)
            {
                float l = normalize(lightPos - p);
                float n = getNormal(p);
                float dif = clamp(dot(n, l) * 0.5 + 0.5, 0, 1);
                float d = raymarchLight(p + n * 0.1 * 10, l);
                d += 1;
                d = clamp(d, 0, 1);
                dif *= d;
                float4col col = {/*r = */dif,
                                 /*g = */dif,
                                 /*b = */dif,
                                 /*a = *//*ddddd- 1};
                float occ = (float(i) / ITERATIONS * 2);
                occ = 1 - occ;
                occ *= occ;
                col.rgb *= occ;
                float fog = distance(p, ro);
                fog /= MAX_DIST;
                fog = clamp(fog, 0, 1);
                fog *= fog;
                col.rgb = col.rgb * (1 - fog) + 0.28 * fog;
                return col;
            }
*/
            float raymarch(float3 ro, float3 rd)
            {
                float3 p = ro;
                for (int i = 0; i < ITERATIONS; i++)
                {
                    float d = getDist(p);
                    if(d > MAX_DIST) return 0;
                    p += rd * d;
                    if(d < 0.001)
                    {
                        return getLight(p, ro, i, float3(0, 50, 0));
                    }
                }
                return 0;
            }











/*


//54747474674745



double signrdDstToCircle(){
    return length(centre-p) - radius;
}

double signedDstToBox(double p, double centre, double size){
    double offset = abs(p-centre) - size;
    //dst from point outside box to edge (0 if inside box)
    double unsignedDst = length(max(offset, 0));
    //-dst from point inside box to edge (0 if outside box)
    double dstInsidebox = max(min(offset, 0));
    return unsignedDst + dstinsidebox;
}

double signedDstToScene(double p){
    double dstToScene = maxDst;

    for(int i = 0; i < NumCircles; i ++){
        float dstToCircle = signedDstToCircle(p, circles[i].centre, circles[i].radius);
        dstToScene = min(dstToCircle, dstToScene);
    }

    for(int i = 0; i < NumBoxes; i ++){
        float dstToBox = signedDstToBox(p, boxes[i].centre, boxes[i].size);
        dstToScene = min(dstToBox, dstToScene);
    }

    return dstToScene;
}

*/
