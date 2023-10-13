xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 358;
 32.59189;-29.58987;1.02004;,
 34.39574;-31.40265;2.87881;,
 34.29111;-27.35267;4.55692;,
 32.53526;-27.39803;1.92823;,
 34.18647;-23.30269;2.87881;,
 32.47863;-25.20620;1.02004;,
 34.14314;-21.62514;-1.17252;,
 32.45517;-24.29832;-1.17252;,
 34.18647;-23.30269;-5.22386;,
 32.47863;-25.20620;-3.36509;,
 34.29111;-27.35267;-6.90197;,
 32.53526;-27.39803;-4.27328;,
 34.39574;-31.40265;-5.22386;,
 32.59189;-29.58987;-3.36509;,
 34.43908;-33.08021;-1.17252;,
 32.61535;-30.49776;-1.17252;,
 37.05564;-32.57633;4.12079;,
 36.91892;-27.28477;6.31336;,
 36.78220;-21.99323;4.12079;,
 36.72559;-19.80139;-1.17252;,
 36.78220;-21.99323;-6.46584;,
 36.91892;-27.28477;-8.65841;,
 37.05564;-32.57633;-6.46585;,
 37.11227;-34.76816;-1.17252;,
 40.16662;-32.93223;4.55692;,
 40.01864;-27.20469;6.93014;,
 39.87067;-21.47716;4.55692;,
 39.80937;-19.10474;-1.17252;,
 39.87067;-21.47716;-6.90197;,
 40.01864;-27.20469;-9.27518;,
 40.16662;-32.93223;-6.90197;,
 40.22792;-35.30465;-1.17252;,
 43.25507;-32.41616;4.12079;,
 43.11835;-27.12461;6.31336;,
 42.98165;-21.83306;4.12079;,
 42.92502;-19.64123;-1.17252;,
 42.98165;-21.83306;-6.46584;,
 43.11835;-27.12461;-8.65841;,
 43.25507;-32.41616;-6.46585;,
 43.31170;-34.60800;-1.17252;,
 45.85082;-31.10670;2.87881;,
 45.74618;-27.05672;4.55692;,
 45.64155;-23.00673;2.87881;,
 45.59819;-21.32918;-1.17252;,
 45.64155;-23.00673;-5.22386;,
 45.74618;-27.05672;-6.90197;,
 45.85082;-31.10670;-5.22386;,
 45.89416;-32.78425;-1.17252;,
 47.55866;-29.20319;1.02004;,
 47.50203;-27.01136;1.92823;,
 47.44540;-24.81952;1.02004;,
 47.42194;-23.91164;-1.17252;,
 47.44540;-24.81952;-3.36509;,
 47.50203;-27.01136;-4.27328;,
 47.55866;-29.20319;-3.36509;,
 47.58212;-30.11107;-1.17252;,
 31.91869;-27.41397;-1.17252;,
 48.11860;-26.99542;-1.17252;,
 39.04861;-36.24652;22.04924;,
 39.04861;-14.17112;32.59701;,
 -39.02245;-14.17112;32.59701;,
 -39.02245;-36.24652;22.04924;,
 39.04861;-14.17112;32.59701;,
 39.04861;-14.17112;-35.22625;,
 -39.02245;-14.17112;-35.22625;,
 -39.02245;-14.17112;32.59701;,
 39.04861;-14.17112;-35.22625;,
 39.04861;-36.24652;-24.67847;,
 -39.02245;-36.24652;-24.67847;,
 -39.02245;-14.17112;-35.22625;,
 39.04861;-36.24652;-24.67847;,
 39.04861;-36.24652;22.04924;,
 -39.02245;-36.24652;22.04924;,
 -39.02245;-36.24652;-24.67847;,
 -39.02245;-36.24652;22.04924;,
 -39.02245;-14.17112;32.59701;,
 -39.02245;-14.17112;-35.22625;,
 -39.02245;-36.24652;-24.67847;,
 39.04861;-36.24652;-24.67847;,
 39.04861;-14.17112;-35.22625;,
 39.04861;-14.17112;32.59701;,
 39.04861;-36.24652;22.04924;,
 -47.02123;-29.58987;1.02004;,
 -45.21737;-31.40265;2.87881;,
 -45.32201;-27.35267;4.55692;,
 -47.07784;-27.39803;1.92823;,
 -45.42663;-23.30269;2.87881;,
 -47.13449;-25.20620;1.02004;,
 -45.46998;-21.62514;-1.17252;,
 -47.15793;-24.29832;-1.17252;,
 -45.42663;-23.30269;-5.22386;,
 -47.13449;-25.20620;-3.36509;,
 -45.32201;-27.35267;-6.90197;,
 -47.07784;-27.39803;-4.27328;,
 -45.21737;-31.40265;-5.22386;,
 -47.02123;-29.58987;-3.36509;,
 -45.17402;-33.08021;-1.17252;,
 -46.99777;-30.49776;-1.17252;,
 -42.55746;-32.57633;4.12079;,
 -42.69418;-27.28477;6.31336;,
 -42.83090;-21.99323;4.12079;,
 -42.88753;-19.80139;-1.17252;,
 -42.83090;-21.99323;-6.46584;,
 -42.69418;-27.28477;-8.65841;,
 -42.55746;-32.57633;-6.46585;,
 -42.50085;-34.76816;-1.17252;,
 -39.44648;-32.93223;4.55692;,
 -39.59447;-27.20469;6.93014;,
 -39.74244;-21.47716;4.55692;,
 -39.80372;-19.10474;-1.17252;,
 -39.74244;-21.47716;-6.90197;,
 -39.59447;-27.20469;-9.27518;,
 -39.44648;-32.93223;-6.90197;,
 -39.38519;-35.30465;-1.17252;,
 -36.35802;-32.41616;4.12079;,
 -36.49474;-27.12461;6.31336;,
 -36.63144;-21.83306;4.12079;,
 -36.68809;-19.64123;-1.17252;,
 -36.63144;-21.83306;-6.46584;,
 -36.49474;-27.12461;-8.65841;,
 -36.35802;-32.41616;-6.46585;,
 -36.30139;-34.60800;-1.17252;,
 -33.76229;-31.10670;2.87881;,
 -33.86693;-27.05672;4.55692;,
 -33.97156;-23.00673;2.87881;,
 -34.01490;-21.32918;-1.17252;,
 -33.97156;-23.00673;-5.22386;,
 -33.86693;-27.05672;-6.90197;,
 -33.76229;-31.10670;-5.22386;,
 -33.71896;-32.78425;-1.17252;,
 -32.05445;-29.20319;1.02004;,
 -32.11106;-27.01136;1.92823;,
 -32.16771;-24.81952;1.02004;,
 -32.19115;-23.91164;-1.17252;,
 -32.16771;-24.81952;-3.36509;,
 -32.11106;-27.01136;-4.27328;,
 -32.05445;-29.20319;-3.36509;,
 -32.03099;-30.11107;-1.17252;,
 -47.69441;-27.41397;-1.17252;,
 -31.49449;-26.99542;-1.17252;,
 15.31869;8.51322;-47.28436;,
 46.97351;8.51322;-47.28436;,
 46.97351;-15.72868;-47.28436;,
 15.31869;-15.72868;-47.28436;,
 15.31869;18.43751;1.68316;,
 15.31869;18.43751;-18.98355;,
 -15.34167;18.47238;-19.09516;,
 -15.29256;18.43751;1.68316;,
 -21.70155;-9.06740;47.28436;,
 21.72769;-9.06740;47.28436;,
 21.09391;14.59645;47.28436;,
 -21.06778;14.59645;47.28436;,
 0.01308;-15.81472;-14.26244;,
 5.74300;-15.77171;-30.77340;,
 15.31869;-15.81472;1.68316;,
 15.31869;-15.77171;-33.13396;,
 15.31869;-15.81473;-18.98355;,
 46.97351;18.43753;-18.98355;,
 46.97351;18.43751;1.68316;,
 46.97351;-15.81472;1.68316;,
 46.97351;-15.81473;-18.98355;,
 -46.94737;18.43751;1.68316;,
 -46.99775;18.45274;-19.11338;,
 -46.94737;-15.81473;-18.98355;,
 -46.94737;-15.81471;1.68316;,
 -15.29256;-15.81472;1.68316;,
 -15.29256;-15.81473;-18.98355;,
 -15.29256;-15.77171;-33.13396;,
 -41.93627;14.59645;47.28436;,
 -41.93627;-9.06740;47.28436;,
 -46.94737;27.73331;-18.98355;,
 -46.94737;36.16714;1.68316;,
 -15.29256;36.16714;1.68316;,
 -15.29256;27.73327;-18.98355;,
 46.97351;36.16714;1.68316;,
 46.97351;27.73331;-18.98355;,
 15.31869;27.73327;-18.98355;,
 15.31869;36.16714;1.68316;,
 41.96240;-9.06740;47.28436;,
 41.96240;14.59645;47.28436;,
 46.97351;-15.81473;-18.98355;,
 46.97351;-15.81471;1.68316;,
 15.31869;-15.81472;1.68316;,
 15.31869;-15.81473;-18.98355;,
 -15.29256;8.51322;-47.28436;,
 -15.29256;-15.72868;-47.28436;,
 -46.94737;-15.72868;-47.28436;,
 -46.94737;8.51322;-47.28436;,
 -46.94737;-15.81472;1.68316;,
 -46.94737;-15.81473;-18.98355;,
 -15.29256;-15.81473;-18.98355;,
 -15.29256;-15.81472;1.68316;,
 -46.94737;-15.77171;-33.13396;,
 -15.29256;-15.77171;-33.13396;,
 -46.94783;16.21470;-33.21145;,
 -46.94737;-15.77171;-33.13396;,
 -46.94783;16.21470;-33.21145;,
 -46.99775;18.45274;-19.11338;,
 -15.34167;18.47238;-19.09516;,
 -15.25475;16.22154;-33.26574;,
 15.31869;16.21470;-33.13395;,
 -15.25475;16.22154;-33.26574;,
 46.97351;18.43753;-18.98355;,
 46.97351;16.21470;-33.13396;,
 46.97351;16.21470;-33.13396;,
 46.97351;-15.77171;-33.13396;,
 46.97351;-15.77171;-33.13396;,
 15.31869;-15.77171;-33.13396;,
 -46.99775;18.45274;-19.11338;,
 -46.94737;27.73331;-18.98355;,
 -15.29256;27.73327;-18.98355;,
 -15.34167;18.47238;-19.09516;,
 -15.34167;18.47238;-19.09516;,
 -15.29256;27.73327;-18.98355;,
 -15.29256;36.16714;1.68316;,
 -15.29256;18.43751;1.68316;,
 -20.77405;29.59436;47.28436;,
 -41.93627;29.59436;47.28436;,
 -46.94737;36.16714;1.68316;,
 -46.94737;27.73331;-18.98355;,
 15.31869;36.16714;1.68316;,
 15.31869;27.73327;-18.98355;,
 15.31869;18.43751;-18.98355;,
 15.31869;18.43751;1.68316;,
 15.31869;18.43751;-18.98355;,
 15.31869;27.73327;-18.98355;,
 46.97351;27.73331;-18.98355;,
 46.97351;18.43753;-18.98355;,
 46.97351;27.73331;-18.98355;,
 46.97351;36.16714;1.68316;,
 41.96240;29.59436;47.28436;,
 20.80020;29.59436;47.28436;,
 -46.94737;-15.81473;43.04611;,
 -15.29256;-15.81473;43.04611;,
 0.01308;-15.81472;-14.26244;,
 20.15561;-15.81473;43.04611;,
 46.97351;-15.81473;43.04611;,
 46.92086;18.43751;43.08904;,
 46.97351;-15.81473;43.04611;,
 46.92445;36.24653;43.08414;,
 15.21275;36.24250;43.14326;,
 46.92445;36.24653;43.08414;,
 15.31869;18.43751;43.04611;,
 15.21275;36.24250;43.14326;,
 -15.29256;18.43751;43.04611;,
 15.31869;18.43751;43.04611;,
 -15.29256;36.24653;43.04611;,
 -15.29256;18.43751;43.04611;,
 -46.94737;36.24653;43.04611;,
 -15.29256;36.24653;43.04611;,
 -46.94737;18.43751;43.04611;,
 -46.94737;36.24653;43.04611;,
 -46.94737;-15.81473;43.04611;,
 -46.94737;8.51322;-47.28436;,
 -46.94783;16.21470;-33.21145;,
 -15.29256;8.51322;-47.28436;,
 15.31869;8.51322;-47.28436;,
 46.97351;8.51322;-47.28436;,
 46.97351;-15.72868;-47.28436;,
 46.97351;8.51322;-47.28436;,
 15.31869;-15.72868;-47.28436;,
 46.97351;-15.72868;-47.28436;,
 5.74300;-15.77171;-30.77340;,
 -15.29256;-15.72868;-47.28436;,
 -46.94737;-15.72868;-47.28436;,
 -46.94737;8.51322;-47.28436;,
 -46.94737;-15.72868;-47.28436;,
 -20.12948;-15.81473;43.04611;,
 -15.29256;-15.81473;43.04611;,
 20.15561;-15.81473;43.04611;,
 15.31869;-15.81473;43.04611;,
 -15.29256;18.43751;43.04611;,
 15.31869;18.43751;43.04611;,
 15.31869;-15.81473;43.04611;,
 -20.12948;-15.81473;43.04611;,
 -46.94737;-15.81473;43.04611;,
 -46.94737;18.43751;43.04611;,
 46.92086;18.43751;43.08904;,
 46.97351;-15.81473;43.04611;,
 -46.94737;36.24653;43.04611;,
 -15.29256;36.24653;43.04611;,
 15.21275;36.24250;43.14326;,
 20.67037;29.59436;47.40375;,
 41.83257;29.59436;47.40375;,
 46.92445;36.24653;43.08414;,
 41.83257;14.59645;47.40375;,
 46.01647;-14.83024;-47.16025;,
 46.01647;-12.31700;-47.16025;,
 64.92963;-12.31700;-47.16025;,
 64.92963;-14.83024;-47.16025;,
 46.01647;1.38100;-20.63129;,
 46.01647;1.70438;42.92085;,
 64.92963;1.70438;42.92085;,
 64.92963;1.38100;-20.63129;,
 46.01647;1.70438;42.92085;,
 46.01647;-0.80885;42.92085;,
 64.92963;-0.80885;42.92085;,
 64.92963;1.70438;42.92085;,
 46.01647;-0.80885;42.92085;,
 46.01647;-1.13224;-20.63129;,
 64.92963;-1.13224;-20.63129;,
 64.92963;-0.80885;42.92085;,
 64.92963;1.38100;-20.63129;,
 64.92963;1.70438;42.92085;,
 64.92963;-0.80885;42.92085;,
 64.92963;-1.13224;-20.63129;,
 46.01647;-0.80885;42.92085;,
 46.01647;1.70438;42.92085;,
 46.01647;1.38100;-20.63129;,
 46.01647;-1.13224;-20.63129;,
 46.01647;-12.31700;-47.16025;,
 64.92963;-12.31700;-47.16025;,
 64.92963;-14.83024;-47.16025;,
 64.92963;-12.31700;-47.16025;,
 46.01647;-14.83024;-47.16025;,
 64.92963;-14.83024;-47.16025;,
 46.01647;-12.31700;-47.16025;,
 46.01647;-14.83024;-47.16025;,
 -64.92963;-14.83024;-47.16025;,
 -64.92963;-12.31700;-47.16025;,
 -46.01649;-12.31700;-47.16025;,
 -46.01649;-14.83024;-47.16025;,
 -64.92963;1.38100;-20.63129;,
 -64.92963;1.70438;42.92085;,
 -46.01649;1.70438;42.92085;,
 -46.01649;1.38100;-20.63129;,
 -64.92963;1.70438;42.92085;,
 -64.92963;-0.80885;42.92085;,
 -46.01649;-0.80885;42.92085;,
 -46.01649;1.70438;42.92085;,
 -64.92963;-0.80885;42.92085;,
 -64.92963;-1.13224;-20.63129;,
 -46.01649;-1.13224;-20.63129;,
 -46.01649;-0.80885;42.92085;,
 -46.01649;1.38100;-20.63129;,
 -46.01649;1.70438;42.92085;,
 -46.01649;-0.80885;42.92085;,
 -46.01649;-1.13224;-20.63129;,
 -64.92963;-0.80885;42.92085;,
 -64.92963;1.70438;42.92085;,
 -64.92963;1.38100;-20.63129;,
 -64.92963;-1.13224;-20.63129;,
 -64.92963;-12.31700;-47.16025;,
 -46.01649;-12.31700;-47.16025;,
 -46.01649;-14.83024;-47.16025;,
 -46.01649;-12.31700;-47.16025;,
 -64.92963;-14.83024;-47.16025;,
 -46.01649;-14.83024;-47.16025;,
 -64.92963;-12.31700;-47.16025;,
 -64.92963;-14.83024;-47.16025;,
 46.97351;-15.81472;1.68316;,
 46.97351;-15.81471;1.68316;,
 46.97351;-15.81473;-18.98355;,
 -46.94737;-15.81473;-18.98355;,
 -46.94737;-15.81472;1.68316;,
 -46.94737;-15.81471;1.68316;,
 -46.94737;-15.81473;43.04611;,
 46.97351;-15.81473;43.04611;;
 
 233;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;7,6,8,9;,
 4;9,8,10,11;,
 4;11,10,12,13;,
 4;13,12,14,15;,
 4;15,14,1,0;,
 4;1,16,17,2;,
 4;2,17,18,4;,
 4;4,18,19,6;,
 4;6,19,20,8;,
 4;8,20,21,10;,
 4;10,21,22,12;,
 4;12,22,23,14;,
 4;14,23,16,1;,
 4;16,24,25,17;,
 4;17,25,26,18;,
 4;18,26,27,19;,
 4;19,27,28,20;,
 4;20,28,29,21;,
 4;21,29,30,22;,
 4;22,30,31,23;,
 4;23,31,24,16;,
 4;24,32,33,25;,
 4;25,33,34,26;,
 4;26,34,35,27;,
 4;27,35,36,28;,
 4;28,36,37,29;,
 4;29,37,38,30;,
 4;30,38,39,31;,
 4;31,39,32,24;,
 4;32,40,41,33;,
 4;33,41,42,34;,
 4;34,42,43,35;,
 4;35,43,44,36;,
 4;36,44,45,37;,
 4;37,45,46,38;,
 4;38,46,47,39;,
 4;39,47,40,32;,
 4;40,48,49,41;,
 4;41,49,50,42;,
 4;42,50,51,43;,
 4;43,51,52,44;,
 4;44,52,53,45;,
 4;45,53,54,46;,
 4;46,54,55,47;,
 4;47,55,48,40;,
 3;3,56,0;,
 3;5,56,3;,
 3;7,56,5;,
 3;9,56,7;,
 3;11,56,9;,
 3;13,56,11;,
 3;15,56,13;,
 3;0,56,15;,
 3;48,57,49;,
 3;49,57,50;,
 3;50,57,51;,
 3;51,57,52;,
 3;52,57,53;,
 3;53,57,54;,
 3;54,57,55;,
 3;55,57,48;,
 4;58,59,60,61;,
 4;62,63,64,65;,
 4;66,67,68,69;,
 4;70,71,72,73;,
 4;74,75,76,77;,
 4;78,79,80,81;,
 4;82,83,84,85;,
 4;85,84,86,87;,
 4;87,86,88,89;,
 4;89,88,90,91;,
 4;91,90,92,93;,
 4;93,92,94,95;,
 4;95,94,96,97;,
 4;97,96,83,82;,
 4;83,98,99,84;,
 4;84,99,100,86;,
 4;86,100,101,88;,
 4;88,101,102,90;,
 4;90,102,103,92;,
 4;92,103,104,94;,
 4;94,104,105,96;,
 4;96,105,98,83;,
 4;98,106,107,99;,
 4;99,107,108,100;,
 4;100,108,109,101;,
 4;101,109,110,102;,
 4;102,110,111,103;,
 4;103,111,112,104;,
 4;104,112,113,105;,
 4;105,113,106,98;,
 4;106,114,115,107;,
 4;107,115,116,108;,
 4;108,116,117,109;,
 4;109,117,118,110;,
 4;110,118,119,111;,
 4;111,119,120,112;,
 4;112,120,121,113;,
 4;113,121,114,106;,
 4;114,122,123,115;,
 4;115,123,124,116;,
 4;116,124,125,117;,
 4;117,125,126,118;,
 4;118,126,127,119;,
 4;119,127,128,120;,
 4;120,128,129,121;,
 4;121,129,122,114;,
 4;122,130,131,123;,
 4;123,131,132,124;,
 4;124,132,133,125;,
 4;125,133,134,126;,
 4;126,134,135,127;,
 4;127,135,136,128;,
 4;128,136,137,129;,
 4;129,137,130,122;,
 3;85,138,82;,
 3;87,138,85;,
 3;89,138,87;,
 3;91,138,89;,
 3;93,138,91;,
 3;95,138,93;,
 3;97,138,95;,
 3;82,138,97;,
 3;130,139,131;,
 3;131,139,132;,
 3;132,139,133;,
 3;133,139,134;,
 3;134,139,135;,
 3;135,139,136;,
 3;136,139,137;,
 3;137,139,130;,
 4;140,141,142,143;,
 4;144,145,146,147;,
 4;148,149,150,151;,
 3;152,153,154;,
 3;153,155,154;,
 3;154,155,156;,
 4;157,158,159,160;,
 4;161,162,163,164;,
 3;165,166,152;,
 3;166,167,152;,
 3;152,167,153;,
 4;168,169,148,151;,
 4;170,171,172,173;,
 4;174,175,176,177;,
 4;149,178,179,150;,
 4;180,181,182,183;,
 4;184,140,143,185;,
 4;186,187,184,185;,
 4;188,189,190,191;,
 4;189,192,193,190;,
 4;162,194,195,163;,
 4;196,197,198,199;,
 4;145,200,201,146;,
 4;202,203,200,145;,
 4;204,157,160,205;,
 4;206,180,183,207;,
 4;208,209,210,211;,
 4;212,213,214,215;,
 4;151,216,217,168;,
 4;218,219,162,161;,
 4;220,221,222,223;,
 4;224,225,226,227;,
 4;157,228,229,158;,
 4;179,230,231,150;,
 4;232,188,191,233;,
 3;234,233,191;,
 4;182,235,233,234;,
 4;181,236,235,182;,
 4;158,237,238,159;,
 4;229,239,237,158;,
 4;240,241,174,177;,
 4;242,243,220,223;,
 4;244,245,144,147;,
 4;214,246,247,215;,
 4;171,248,249,172;,
 4;250,251,218,161;,
 4;252,250,161,164;,
 4;253,254,201,255;,
 4;200,256,255,201;,
 4;203,257,256,200;,
 4;258,259,204,205;,
 4;260,261,206,207;,
 3;260,207,262;,
 4;263,260,262,193;,
 4;192,264,263,193;,
 4;194,265,266,195;,
 4;267,268,269,270;,
 4;271,151,150,272;,
 4;273,149,148,274;,
 4;274,148,169,275;,
 4;275,169,168,276;,
 4;277,179,178,278;,
 4;278,178,149,273;,
 4;276,168,217,279;,
 4;279,217,216,280;,
 4;280,216,151,271;,
 4;272,150,231,281;,
 4;281,282,283,284;,
 4;284,283,285,277;,
 4;286,287,288,289;,
 4;290,291,292,293;,
 4;294,295,296,297;,
 4;298,299,300,301;,
 4;302,303,304,305;,
 4;306,307,308,309;,
 4;310,290,293,311;,
 4;312,313,302,305;,
 4;299,314,315,300;,
 4;308,316,317,309;,
 4;318,319,320,321;,
 4;322,323,324,325;,
 4;326,327,328,329;,
 4;330,331,332,333;,
 4;334,335,336,337;,
 4;338,339,340,341;,
 4;342,322,325,343;,
 4;344,345,334,337;,
 4;331,346,347,332;,
 4;340,348,349,341;,
 4;230,283,282,231;,
 3;231,282,281;,
 3;277,285,179;,
 4;179,285,283,230;,
 3;350,351,352;,
 3;353,354,355;,
 3;356,268,267;,
 3;355,354,356;,
 3;270,269,357;,
 3;357,351,350;;
 
 MeshMaterialList {
  1;
  233;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\legTank.png";
   }
  }
 }
 MeshNormals {
  215;
  -0.917476;-0.292926;0.269132;,
  -0.924427;-0.023883;0.380610;,
  -0.931378;0.245159;0.269133;,
  -0.934257;0.356600;0.000000;,
  -0.931378;0.245159;-0.269132;,
  -0.924427;-0.023883;-0.380610;,
  -0.917476;-0.292926;-0.269131;,
  -0.914597;-0.404367;0.000000;,
  -0.696119;-0.516645;0.498494;,
  -0.708994;-0.018318;0.704976;,
  -0.721869;0.480010;0.498493;,
  -0.727201;0.686425;0.000000;,
  -0.721869;0.480010;-0.498493;,
  -0.708994;-0.018317;-0.704977;,
  -0.696119;-0.516645;-0.498494;,
  -0.690786;-0.723059;0.000000;,
  -0.367564;-0.662447;0.652733;,
  -0.384423;-0.009932;0.923104;,
  -0.401281;0.642583;0.652733;,
  -0.408264;0.912864;0.000000;,
  -0.401281;0.642584;-0.652733;,
  -0.384422;-0.009931;-0.923104;,
  -0.367563;-0.662447;-0.652733;,
  -0.360580;-0.932728;0.000000;,
  0.018263;-0.706871;0.707107;,
  0.000000;0.000000;1.000000;,
  -0.018262;0.706871;0.707106;,
  -0.025827;0.999666;0.000000;,
  -0.018262;0.706871;-0.707107;,
  0.000000;0.000001;-1.000000;,
  0.018263;-0.706871;-0.707107;,
  0.025827;-0.999667;0.000000;,
  0.401280;-0.642583;0.652734;,
  0.384421;0.009932;0.923104;,
  0.367563;0.662448;0.652733;,
  0.360580;0.932728;0.000000;,
  0.367563;0.662448;-0.652733;,
  0.384421;0.009932;-0.923105;,
  0.401280;-0.642583;-0.652734;,
  0.408263;-0.912864;0.000000;,
  0.721868;-0.480010;0.498495;,
  0.708993;0.018317;0.704978;,
  0.696119;0.516646;0.498494;,
  0.690785;0.723060;0.000000;,
  0.696119;0.516646;-0.498494;,
  0.708993;0.018318;-0.704978;,
  0.721868;-0.480010;-0.498494;,
  0.727201;-0.686425;0.000000;,
  0.931378;-0.245158;0.269132;,
  0.924427;0.023884;0.380610;,
  0.917476;0.292926;0.269131;,
  0.914596;0.404368;0.000000;,
  0.917476;0.292926;-0.269131;,
  0.924427;0.023884;-0.380610;,
  0.931378;-0.245158;-0.269132;,
  0.934257;-0.356599;0.000000;,
  -0.999667;-0.025828;0.000000;,
  0.999666;0.025829;0.000000;,
  0.000000;-0.431122;0.902294;,
  0.000000;1.000000;0.000000;,
  0.000000;-0.431122;-0.902294;,
  -0.917477;-0.292923;0.269132;,
  -0.924427;-0.023884;0.380611;,
  -0.931379;0.245157;0.269130;,
  -0.934257;0.356601;0.000000;,
  -0.931379;0.245157;-0.269130;,
  -0.924427;-0.023883;-0.380611;,
  -0.917477;-0.292922;-0.269131;,
  -0.914597;-0.404366;0.000000;,
  -0.696118;-0.516645;0.498495;,
  -0.708993;-0.018317;0.704977;,
  -0.721869;0.480010;0.498494;,
  -0.727201;0.686425;0.000000;,
  -0.721868;0.480011;-0.498494;,
  -0.708993;-0.018317;-0.704977;,
  -0.696119;-0.516645;-0.498494;,
  -0.690784;-0.723061;0.000000;,
  -0.367563;-0.662447;0.652733;,
  -0.384422;-0.009932;0.923104;,
  -0.401281;0.642583;0.652733;,
  -0.408264;0.912864;0.000000;,
  -0.401280;0.642584;-0.652733;,
  -0.384421;-0.009931;-0.923104;,
  -0.367563;-0.662447;-0.652733;,
  -0.360580;-0.932728;0.000000;,
  0.018262;-0.706871;0.707107;,
  -0.000001;0.000000;1.000000;,
  -0.018262;0.706871;0.707106;,
  -0.025826;0.999666;0.000000;,
  -0.018262;0.706871;-0.707107;,
  -0.000001;0.000001;-1.000000;,
  0.018262;-0.706871;-0.707107;,
  0.025827;-0.999666;0.000000;,
  0.401281;-0.642583;0.652733;,
  0.384423;0.009932;0.923104;,
  0.367564;0.662447;0.652733;,
  0.360580;0.932728;0.000000;,
  0.367564;0.662448;-0.652733;,
  0.384422;0.009932;-0.923104;,
  0.401281;-0.642583;-0.652733;,
  0.408264;-0.912864;0.000000;,
  0.721869;-0.480010;0.498493;,
  0.708993;0.018318;0.704977;,
  0.696118;0.516645;0.498494;,
  0.690786;0.723060;0.000000;,
  0.696118;0.516646;-0.498494;,
  0.708993;0.018318;-0.704978;,
  0.721869;-0.480011;-0.498493;,
  0.727202;-0.686424;0.000000;,
  0.931377;-0.245163;0.269132;,
  0.924427;0.023884;0.380611;,
  0.917475;0.292929;0.269134;,
  0.914597;0.404367;0.000000;,
  0.917475;0.292929;-0.269134;,
  0.924427;0.023884;-0.380611;,
  0.931377;-0.245163;-0.269132;,
  0.934256;-0.356603;0.000000;,
  -0.999666;-0.025827;0.000000;,
  0.999666;0.025827;0.000000;,
  0.000000;0.000000;-1.000000;,
  -0.907131;0.000000;0.420849;,
  0.868626;-0.015096;0.495239;,
  0.000000;-0.875188;0.483783;,
  0.000000;-0.875188;0.483783;,
  0.000000;0.000000;-0.000000;,
  0.000000;0.932999;0.359879;,
  -0.894443;-0.007148;0.447125;,
  -1.000000;-0.000495;-0.000147;,
  -1.000000;0.000405;0.000257;,
  0.000454;0.994546;-0.104293;,
  0.000622;0.994604;-0.103739;,
  1.000000;0.000000;0.000000;,
  0.000001;0.925872;-0.377838;,
  0.895600;-0.003262;0.444849;,
  0.000000;0.877197;0.480131;,
  -0.000001;0.925872;-0.377838;,
  0.000390;0.878661;0.477445;,
  0.907155;-0.000033;0.420796;,
  -1.000000;-0.000184;0.000303;,
  1.000000;0.000384;0.000318;,
  1.000000;0.000167;0.000466;,
  -0.000034;0.981113;-0.193437;,
  0.000284;1.000000;0.000420;,
  0.000000;0.981108;-0.193462;,
  -1.000000;0.000491;0.000606;,
  -1.000000;-0.000378;-0.000835;,
  0.000358;0.946329;-0.323205;,
  0.000614;0.946730;-0.322027;,
  -0.000000;0.946972;-0.321315;,
  0.000000;-0.999995;-0.003040;,
  -0.000264;-0.999997;-0.002589;,
  0.000278;-0.999997;-0.002304;,
  0.000536;-0.999999;-0.001243;,
  0.000338;-1.000000;-0.000630;,
  -1.000000;0.000000;0.000000;,
  0.000278;-0.999996;-0.002890;,
  0.000235;-0.999999;-0.001520;,
  0.000000;-1.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  -0.000000;-1.000000;-0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;-0.276765;0.960938;,
  0.132252;0.160912;0.978068;,
  -0.131060;0.159958;0.978385;,
  -0.343853;0.000000;0.939023;,
  -0.235586;-0.194047;0.952284;,
  0.353279;-0.018630;0.935333;,
  0.235622;-0.194044;0.952276;,
  -0.235776;0.196184;0.951799;,
  0.218905;0.192562;0.956557;,
  -0.315684;-0.005170;0.948850;,
  0.000000;0.000000;1.000000;,
  0.000000;0.999987;-0.005088;,
  0.000000;0.971133;-0.238540;,
  0.000000;-0.971133;0.238540;,
  0.000000;0.971133;-0.238540;,
  0.000000;-0.971133;0.238540;,
  0.357421;0.299473;0.884627;,
  0.000750;0.542523;0.840040;,
  0.661563;-0.034851;0.749079;,
  0.000000;-1.000000;-0.000000;,
  0.000000;-0.999999;-0.001520;,
  0.000000;-0.999999;-0.001520;,
  -0.000512;0.946169;-0.323672;,
  -0.000502;0.987625;-0.156831;,
  -0.000000;0.987886;-0.155182;,
  0.000284;0.013018;-0.999915;,
  0.999996;-0.002637;-0.001186;,
  0.999999;-0.001319;-0.000593;,
  -0.999999;0.001349;0.000607;,
  -0.999996;0.002697;0.001213;,
  -0.999999;-0.001484;-0.000636;,
  1.000000;-0.000050;0.000614;,
  0.907020;0.000433;0.421087;,
  -0.907131;0.000000;0.420849;,
  -0.960792;0.000000;0.277270;,
  -0.000507;0.876749;-0.480947;,
  0.000311;0.877027;-0.480441;,
  0.000564;0.877821;-0.478989;,
  -0.000000;0.878337;-0.478042;,
  -0.000193;-0.999996;-0.002968;,
  0.000000;-0.999995;-0.003041;,
  0.000085;-0.999996;-0.002932;,
  -1.000000;-0.000007;-0.000017;,
  0.000000;-0.531908;0.846802;,
  0.000000;-0.999987;0.005089;,
  0.000000;0.888544;-0.458792;,
  0.000000;-0.888544;0.458792;,
  0.000000;-0.999987;0.005089;,
  0.000000;0.888544;-0.458792;,
  0.000000;-0.888544;0.458792;,
  -0.254805;-0.926444;-0.277083;,
  -0.472126;-0.716598;-0.513405;,
  -0.676901;0.000000;-0.736074;;
  233;
  4;0,8,9,1;,
  4;1,9,10,2;,
  4;2,10,11,3;,
  4;3,11,12,4;,
  4;4,12,13,5;,
  4;5,13,14,6;,
  4;6,14,15,7;,
  4;7,15,8,0;,
  4;8,16,17,9;,
  4;9,17,18,10;,
  4;10,18,19,11;,
  4;11,19,20,12;,
  4;12,20,21,13;,
  4;13,21,22,14;,
  4;14,22,23,15;,
  4;15,23,16,8;,
  4;16,24,25,17;,
  4;17,25,26,18;,
  4;18,26,27,19;,
  4;19,27,28,20;,
  4;20,28,29,21;,
  4;21,29,30,22;,
  4;22,30,31,23;,
  4;23,31,24,16;,
  4;24,32,33,25;,
  4;25,33,34,26;,
  4;26,34,35,27;,
  4;27,35,36,28;,
  4;28,36,37,29;,
  4;29,37,38,30;,
  4;30,38,39,31;,
  4;31,39,32,24;,
  4;32,40,41,33;,
  4;33,41,42,34;,
  4;34,42,43,35;,
  4;35,43,44,36;,
  4;36,44,45,37;,
  4;37,45,46,38;,
  4;38,46,47,39;,
  4;39,47,40,32;,
  4;40,48,49,41;,
  4;41,49,50,42;,
  4;42,50,51,43;,
  4;43,51,52,44;,
  4;44,52,53,45;,
  4;45,53,54,46;,
  4;46,54,55,47;,
  4;47,55,48,40;,
  3;1,56,0;,
  3;2,56,1;,
  3;3,56,2;,
  3;4,56,3;,
  3;5,56,4;,
  3;6,56,5;,
  3;7,56,6;,
  3;0,56,7;,
  3;48,57,49;,
  3;49,57,50;,
  3;50,57,51;,
  3;51,57,52;,
  3;52,57,53;,
  3;53,57,54;,
  3;54,57,55;,
  3;55,57,48;,
  4;58,58,58,58;,
  4;59,59,59,59;,
  4;60,60,60,60;,
  4;181,181,181,181;,
  4;154,154,154,154;,
  4;131,131,131,131;,
  4;61,69,70,62;,
  4;62,70,71,63;,
  4;63,71,72,64;,
  4;64,72,73,65;,
  4;65,73,74,66;,
  4;66,74,75,67;,
  4;67,75,76,68;,
  4;68,76,69,61;,
  4;69,77,78,70;,
  4;70,78,79,71;,
  4;71,79,80,72;,
  4;72,80,81,73;,
  4;73,81,82,74;,
  4;74,82,83,75;,
  4;75,83,84,76;,
  4;76,84,77,69;,
  4;77,85,86,78;,
  4;78,86,87,79;,
  4;79,87,88,80;,
  4;80,88,89,81;,
  4;81,89,90,82;,
  4;82,90,91,83;,
  4;83,91,92,84;,
  4;84,92,85,77;,
  4;85,93,94,86;,
  4;86,94,95,87;,
  4;87,95,96,88;,
  4;88,96,97,89;,
  4;89,97,98,90;,
  4;90,98,99,91;,
  4;91,99,100,92;,
  4;92,100,93,85;,
  4;93,101,102,94;,
  4;94,102,103,95;,
  4;95,103,104,96;,
  4;96,104,105,97;,
  4;97,105,106,98;,
  4;98,106,107,99;,
  4;99,107,108,100;,
  4;100,108,101,93;,
  4;101,109,110,102;,
  4;102,110,111,103;,
  4;103,111,112,104;,
  4;104,112,113,105;,
  4;105,113,114,106;,
  4;106,114,115,107;,
  4;107,115,116,108;,
  4;108,116,109,101;,
  3;62,117,61;,
  3;63,117,62;,
  3;64,117,63;,
  3;65,117,64;,
  3;66,117,65;,
  3;67,117,66;,
  3;68,117,67;,
  3;61,117,68;,
  3;109,118,110;,
  3;110,118,111;,
  3;111,118,112;,
  3;112,118,113;,
  3;113,118,114;,
  3;114,118,115;,
  3;115,118,116;,
  3;116,118,109;,
  4;119,119,119,119;,
  4;142,130,129,142;,
  4;162,162,164,163;,
  3;152,151,153;,
  3;151,150,153;,
  3;154,154,154;,
  4;131,140,139,131;,
  4;144,128,127,138;,
  3;157,156,152;,
  3;156,155,152;,
  3;152,155,151;,
  4;165,166,162,163;,
  4;132,143,143,132;,
  4;141,135,135,141;,
  4;162,168,167,164;,
  4;182,158,153,182;,
  4;119,119,119,119;,
  4;119,119,119,119;,
  4;159,183,156,157;,
  4;183,149,155,156;,
  4;128,145,145,127;,
  4;184,185,129,146;,
  4;130,147,146,129;,
  4;186,148,147,130;,
  4;131,131,131,131;,
  4;149,182,182,150;,
  4;187,187,187,187;,
  4;188,188,189,189;,
  4;163,170,169,165;,
  4;190,191,128,144;,
  4;192,154,154,192;,
  4;119,119,119,119;,
  4;131,131,193,140;,
  4;167,172,171,164;,
  4;122,159,157,160;,
  3;152,160,157;,
  4;153,161,160,152;,
  4;158,123,161,153;,
  4;140,121,194,139;,
  4;193,137,121,140;,
  4;136,136,141,141;,
  4;126,126,192,192;,
  4;125,125,142,142;,
  4;189,133,133,189;,
  4;143,134,134,143;,
  4;120,195,190,144;,
  4;196,120,144,138;,
  4;197,184,146,198;,
  4;147,199,198,146;,
  4;148,200,199,147;,
  4;131,131,131,131;,
  4;201,202,149,150;,
  3;201,150,151;,
  4;203,201,151,155;,
  4;149,202,203,155;,
  4;145,204,204,145;,
  4;124,124,124,124;,
  4;125,163,164,125;,
  4;205,162,162,205;,
  4;205,162,166,122;,
  4;196,166,165,120;,
  4;121,167,168,194;,
  4;123,168,162,205;,
  4;120,165,169,195;,
  4;134,169,170,134;,
  4;133,170,163,133;,
  4;126,164,171,126;,
  4;136,179,178,136;,
  4;137,178,180,121;,
  4;119,119,119,119;,
  4;174,173,173,174;,
  4;172,172,172,172;,
  4;206,175,175,206;,
  4;131,131,131,131;,
  4;154,154,154,154;,
  4;207,174,174,207;,
  4;131,131,131,131;,
  4;175,208,208,175;,
  4;154,154,154,154;,
  4;119,119,119,119;,
  4;176,173,173,176;,
  4;172,172,172,172;,
  4;209,177,177,209;,
  4;131,131,131,131;,
  4;154,154,154,154;,
  4;210,176,176,210;,
  4;131,131,131,131;,
  4;177,211,211,177;,
  4;154,154,154,154;,
  4;181,181,212,212;,
  3;212,212,213;,
  3;121,180,167;,
  4;214,214,214,214;,
  3;154,154,154;,
  3;127,154,138;,
  3;124,124,124;,
  3;138,154,196;,
  3;124,124,124;,
  3;154,154,154;;
 }
 MeshTextureCoords {
  358;
  0.957850;0.967504;,
  0.961668;0.963571;,
  0.961447;0.960019;,
  0.957730;0.965582;,
  0.961225;0.963571;,
  0.957610;0.967504;,
  0.961133;0.972144;,
  0.957560;0.972144;,
  0.961225;0.980717;,
  0.957610;0.976784;,
  0.961447;0.984269;,
  0.957730;0.978706;,
  0.961668;0.980717;,
  0.957850;0.976784;,
  0.961760;0.972144;,
  0.957899;0.972144;,
  0.967299;0.960942;,
  0.967010;0.956302;,
  0.966720;0.960942;,
  0.966600;0.972144;,
  0.966720;0.983346;,
  0.967010;0.987986;,
  0.967299;0.983346;,
  0.967419;0.972144;,
  0.973885;0.960019;,
  0.973571;0.954997;,
  0.973258;0.960019;,
  0.973128;0.972144;,
  0.973258;0.984269;,
  0.973571;0.989291;,
  0.973885;0.984269;,
  0.974014;0.972144;,
  0.980422;0.960942;,
  0.980133;0.956302;,
  0.979844;0.960942;,
  0.979724;0.972144;,
  0.979844;0.983346;,
  0.980133;0.987986;,
  0.980422;0.983346;,
  0.980542;0.972144;,
  0.985917;0.963571;,
  0.985696;0.960019;,
  0.985474;0.963571;,
  0.985383;0.972144;,
  0.985474;0.980717;,
  0.985696;0.984269;,
  0.985917;0.980717;,
  0.986009;0.972144;,
  0.989533;0.967504;,
  0.989413;0.965582;,
  0.989293;0.967504;,
  0.989243;0.972144;,
  0.989293;0.976784;,
  0.989413;0.978706;,
  0.989533;0.976784;,
  0.989582;0.972144;,
  0.956425;0.972144;,
  0.990718;0.972144;,
  0.203647;0.474222;,
  0.203647;0.425678;,
  0.016404;0.425678;,
  0.016404;0.474222;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.203647;0.425678;,
  0.203647;0.474222;,
  0.016404;0.474222;,
  0.016404;0.425678;,
  0.198216;0.628689;,
  0.198216;0.496436;,
  0.030178;0.496436;,
  0.030178;0.628689;,
  0.176179;0.403903;,
  0.206979;0.345223;,
  0.008933;0.345223;,
  0.039733;0.403903;,
  0.039733;0.403903;,
  0.008933;0.345223;,
  0.206979;0.345223;,
  0.176179;0.403903;,
  0.956109;0.967064;,
  0.960233;0.962816;,
  0.959994;0.958981;,
  0.955980;0.964989;,
  0.959755;0.962816;,
  0.955850;0.967064;,
  0.959656;0.972075;,
  0.955796;0.972075;,
  0.959755;0.981335;,
  0.955850;0.977086;,
  0.959994;0.985170;,
  0.955980;0.979162;,
  0.960233;0.981335;,
  0.956109;0.977086;,
  0.960332;0.972075;,
  0.956163;0.972075;,
  0.966314;0.959977;,
  0.966002;0.954966;,
  0.965689;0.959977;,
  0.965560;0.972075;,
  0.965689;0.984173;,
  0.966002;0.989184;,
  0.966314;0.984173;,
  0.966444;0.972075;,
  0.973427;0.958981;,
  0.973088;0.953557;,
  0.972750;0.958981;,
  0.972610;0.972075;,
  0.972750;0.985170;,
  0.973088;0.990594;,
  0.973427;0.985170;,
  0.973567;0.972075;,
  0.980488;0.959977;,
  0.980175;0.954966;,
  0.979863;0.959977;,
  0.979733;0.972075;,
  0.979863;0.984173;,
  0.980175;0.989184;,
  0.980488;0.984173;,
  0.980617;0.972075;,
  0.986422;0.962816;,
  0.986183;0.958981;,
  0.985944;0.962816;,
  0.985845;0.972075;,
  0.985944;0.981335;,
  0.986183;0.985170;,
  0.986422;0.981335;,
  0.986521;0.972075;,
  0.990327;0.967064;,
  0.990197;0.964989;,
  0.990068;0.967064;,
  0.990014;0.972075;,
  0.990068;0.977086;,
  0.990197;0.979162;,
  0.990327;0.977086;,
  0.990380;0.972075;,
  0.954570;0.972075;,
  0.991607;0.972075;,
  0.668043;0.383800;,
  0.737841;0.383800;,
  0.737841;0.450914;,
  0.668043;0.450914;,
  0.708409;0.201674;,
  0.708409;0.267550;,
  0.614564;0.267550;,
  0.614564;0.201674;,
  0.474107;0.596363;,
  0.591584;0.596363;,
  0.589870;0.534346;,
  0.475821;0.534346;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.781005;0.460494;,
  0.850846;0.460494;,
  0.850846;0.609262;,
  0.781005;0.609262;,
  0.850846;0.460494;,
  0.781005;0.460494;,
  0.781005;0.609262;,
  0.850846;0.609262;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.419372;0.534346;,
  0.419372;0.596363;,
  0.507932;0.237954;,
  0.507932;0.177168;,
  0.594474;0.177168;,
  0.594474;0.237954;,
  0.827395;0.177769;,
  0.827395;0.234628;,
  0.733275;0.234628;,
  0.733275;0.177769;,
  0.646319;0.596363;,
  0.646319;0.534346;,
  0.494943;0.416635;,
  0.494943;0.391999;,
  0.458650;0.391999;,
  0.458650;0.416635;,
  0.600545;0.383800;,
  0.600545;0.450914;,
  0.530747;0.450914;,
  0.530747;0.383800;,
  0.387262;0.391999;,
  0.387262;0.416635;,
  0.423554;0.416635;,
  0.423554;0.391999;,
  0.387262;0.433504;,
  0.423554;0.433504;,
  0.733186;0.470149;,
  0.733186;0.609076;,
  0.517520;0.313966;,
  0.517520;0.268861;,
  0.614564;0.268861;,
  0.614564;0.313966;,
  0.708409;0.312655;,
  0.614564;0.312655;,
  0.805452;0.267550;,
  0.805452;0.312655;,
  0.733186;0.470149;,
  0.733186;0.609076;,
  0.494943;0.433504;,
  0.458650;0.433504;,
  0.511203;0.266179;,
  0.511203;0.244317;,
  0.594422;0.244317;,
  0.594422;0.266179;,
  0.927421;0.281472;,
  0.888207;0.281717;,
  0.852184;0.210700;,
  0.926976;0.210232;,
  0.476616;0.495041;,
  0.419372;0.495041;,
  0.850846;0.383489;,
  0.781005;0.420120;,
  0.852184;0.210700;,
  0.888207;0.281717;,
  0.927421;0.281472;,
  0.926976;0.210232;,
  0.736954;0.264403;,
  0.736954;0.240089;,
  0.821039;0.240089;,
  0.821039;0.264403;,
  0.781005;0.420120;,
  0.850846;0.383489;,
  0.646319;0.495041;,
  0.589075;0.495041;,
  0.387262;0.342690;,
  0.423554;0.342690;,
  0.441102;0.411007;,
  0.464196;0.342690;,
  0.494943;0.342690;,
  0.990626;0.460494;,
  0.990626;0.609262;,
  0.990626;0.383144;,
  0.733275;0.063972;,
  0.827395;0.063972;,
  0.926084;0.067649;,
  0.850957;0.068119;,
  0.614564;0.069828;,
  0.708409;0.069828;,
  0.850957;0.068119;,
  0.926084;0.067649;,
  0.507932;0.055510;,
  0.594474;0.055510;,
  0.990626;0.460494;,
  0.990626;0.383144;,
  0.990626;0.609262;,
  0.517520;0.357760;,
  0.517520;0.312655;,
  0.614564;0.357760;,
  0.708409;0.357760;,
  0.805452;0.357760;,
  0.685366;0.608889;,
  0.685366;0.503599;,
  0.458650;0.450372;,
  0.494943;0.450372;,
  0.447672;0.430690;,
  0.423554;0.450372;,
  0.387262;0.450372;,
  0.685366;0.503599;,
  0.685366;0.608889;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.491443;0.524280;,
  0.574248;0.524280;,
  0.574248;0.614046;,
  0.478360;0.614046;,
  0.405817;0.614046;,
  0.405817;0.524280;,
  0.659699;0.524280;,
  0.659875;0.614046;,
  0.405817;0.477607;,
  0.491443;0.477607;,
  0.574072;0.477607;,
  0.588724;0.495041;,
  0.645968;0.495041;,
  0.659523;0.477607;,
  0.645968;0.534346;,
  0.302570;0.547630;,
  0.302570;0.533741;,
  0.375392;0.533741;,
  0.375392;0.547630;,
  0.311912;0.462701;,
  0.311912;0.334054;,
  0.368152;0.334054;,
  0.368152;0.462701;,
  0.515795;0.246522;,
  0.515795;0.265891;,
  0.589399;0.265891;,
  0.589399;0.246522;,
  0.311912;0.334054;,
  0.311912;0.462701;,
  0.368152;0.462701;,
  0.368152;0.334054;,
  0.233246;0.472591;,
  0.230259;0.328906;,
  0.238277;0.328797;,
  0.241264;0.472482;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.311912;0.516403;,
  0.368152;0.516403;,
  0.285780;0.531873;,
  0.277762;0.531982;,
  0.311912;0.516403;,
  0.368152;0.516403;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.302786;0.547630;,
  0.302786;0.533741;,
  0.375608;0.533741;,
  0.375608;0.547630;,
  0.311921;0.462701;,
  0.311921;0.334054;,
  0.368161;0.334054;,
  0.368161;0.462701;,
  0.517446;0.246523;,
  0.517446;0.264099;,
  0.583842;0.264099;,
  0.583842;0.246523;,
  0.311921;0.334054;,
  0.311921;0.462701;,
  0.368161;0.462701;,
  0.368161;0.334054;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.238277;0.328797;,
  0.230259;0.328906;,
  0.233246;0.472591;,
  0.241264;0.472482;,
  0.311921;0.516403;,
  0.368161;0.516403;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.311921;0.516403;,
  0.368161;0.516403;,
  0.277762;0.531982;,
  0.285780;0.531873;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;;
 }
}