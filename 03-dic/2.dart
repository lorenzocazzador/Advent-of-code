import 'dart:io';

import 'dart:math';

List getSegments(List l) {
  Point precP = Point(0,0);
  List res = [];
  int p = 0;

  for(dynamic x in l) {
    String d = x.toString().substring(0,1);
    int v = int.parse(x.toString().substring(1));
    Point newPoint;
    switch(d) {
      case 'L':
        newPoint = Point(precP.x-v,precP.y);
        res.add([newPoint, precP, p, 0]);
        break;
      case 'R':
        newPoint = Point(precP.x+v,precP.y);
        res.add([precP, newPoint, p, 1]);
        break;
      case 'U':
        newPoint = Point(precP.x,precP.y+v);
        res.add([precP, newPoint, p, 1]);
        break;
      case 'D':
        newPoint = Point(precP.x,precP.y-v);
        res.add([newPoint, precP, p, 0]);
        break;
    }
    p += v;
    precP = newPoint;
  }
  return res;
}

Point intersect(List s1, List s2) {
  String p1 = s1[0].x == s1[1].x ? 'py' : 'px',
         p2 = s2[0].x == s2[1].x ? 'py' : 'px';
  
  // if the 2 segments are parallel they don't intersect
  if(p1 == p2) 
    return Point(0,0);
  
  if(p1 == 'py' &&
     s1[0].y <= s2[0].y && s1[1].y >= s2[0].y && 
     s2[0].x <= s1[0].x && s2[1].x >= s1[0].x) {
       int a1 = (s1[3] == 1 ? s1[0].y : s1[1].y),
           a2 = (s2[3] == 1 ? s2[0].x : s2[1].x); 
       return Point((s2[0].y-a1).abs(), (s1[0].x-a2).abs());
  }
  else if(p1 == 'px' &&
    s1[0].x <= s2[0].x && s1[1].x >= s2[0].x &&
    s2[0].y <= s1[0].y && s2[1].y >= s1[0].y){
      int a1 = (s1[3] == 1 ? s1[0].x : s1[1].x),
          a2 = (s2[3] == 1 ? s2[0].y : s2[1].y);

      return Point((a1-s2[0].x).abs(),(s1[0].y-a2).abs()); 
  }

  return Point(0,0);  
}

main() {
  List f = stdin.readLineSync().split(',');
  List s = stdin.readLineSync().split(',');

  List sf = getSegments(f), ss = getSegments(s);

  //print('$sf\n$ss');
  int res;
  for(int i=0; i<sf.length; i++) {
    List segF = sf[i];
    for(int j=0; j<ss.length; j++) {
      List segS = ss[j];

      if(segF[0] == Point(0,0) && segS[0] == Point(0,0))
        continue;
        
      Point tmp = intersect(segF, segS);
      
      //if(tmp != Point(0,0)) 
      //  print(tmp);

      if(tmp != Point(0,0)) {
        int tRes = segF[2] + tmp.x + segS[2] + tmp.y;
        res = (res == null ? tRes : min(res, tRes));
      }
    }
  }

  print('res --> $res');
}