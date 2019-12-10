import 'dart:collection';
import 'dart:io';
import 'dart:math';

List<Point> l = [];

int findStation(Point p) {
  Map<double, List<bool>> m = {}; 
  for(Point x in l) {
    if(x != p) {
      bool up = (x.y != p.y ? x.y > p.y : x.x > p.x);
      double slope = (p.x-x.x)/(p.y-x.y);
      
      if(!m.containsKey(slope))
        m[slope] = [false, false];

      if(up)
        m[slope][0] = true;
      else 
        m[slope][1] = true;
    }
  }
  //print(s);
  int res = 0;
  m.forEach((d, l) {
    res += (l[0] ? 1 : 0) + (l[1] ? 1 : 0);
  });
  return res;
}

class PointSlope{
  double slope;
  bool right;

  PointSlope(this.slope, this.right);

  String toString() {
    return '[' + slope.toString() + ', ' + right.toString() + ']'; 
  }
}

int compare(PointSlope a, PointSlope b) {
  if(a.slope == b.slope && a.right == b.right)
    return 0;

  if(a.right != b.right)
    return a.right ? -1 : 1; 
  else if(a.slope == 0 || b.slope == 0)
    return a.slope == 0 ? -1 : 1;
  else if((a.slope < 0 && b.slope > 0) || (a.slope > 0 && b.slope < 0))
    return a.slope < 0 ? -1 : 1;
  else 
    return a.slope > b.slope ? -1 : 1;
}

Point p1;
double dist(Point a, Point b) {
  return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

int compare2(Point a, Point b) {
  if(a.x == b.x && a.y == b.y)
    return 0;
  else
    return (dist(p1, a) < dist(p1,b) ? -1 : 1);
}

int solve(Point p) {
  p1 = p;
  SplayTreeMap<PointSlope, SplayTreeSet<Point>> m = SplayTreeMap(compare);
  for(Point x in l) {
    if(x != p) {
      bool right = (x.x != p.x ? x.x > p.x : x.y < p.y);
      double slope = (p.x-x.x)/(p.y-x.y);

      PointSlope ps = PointSlope(slope, right);
      if(!m.containsKey(ps)) 
        m[ps] = SplayTreeSet(compare2);
      
      m[ps].add(x);

      //if(p == Point(1,1))
        //print('${i++}: $x -> $slope $right');
    }
  }

  int i = 0;
  bool finish = false;
  Point res;
  
  while(!finish && i<200) {
    bool tmp_f = true;
    m.forEach((ps, l2){
      if(l2.length > 0) {
        Point pf = l2.first;
        l2.remove(pf);
        i++;

        if(i <= 200)
          res = pf;
        
        if(tmp_f)
          tmp_f = (l2.length == 0);
      } 
    });
    finish = tmp_f;
  }
  return res != null ? (res.x*100+res.y) : -1;
}

/*
###
###
###

####
####
####
*/

main() {
  int i=0;
  while(true) {
    String s = stdin.readLineSync();

    if(s == '')
      break;

    for(int j=0; j<s.length; j++)
      if(s[j] == '#')
        l.add(Point(j,i));
    i++;
  }

  Point station;
  int best = 0;
  for(Point p in l) {
    int tmp = findStation(p);
    if(best < tmp) {
      best = tmp;
      station = p;
    }
  }

  int res = solve(station);
  print('res --> $res');
}