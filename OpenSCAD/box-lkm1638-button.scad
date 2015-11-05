difference() {
  union() {
    translate([0,0,4.5]) cylinder(d1=5.45,d2=4.75,h=0.5);
    cylinder(d=5.45,h=4.5);
  }
  translate([0,0,0.5]) cylinder(d=4.4,h=2);
  translate([0,0,2.5]) cylinder(d1=4.4,d2=0,h=1.5);
}
//translate([0,0,0.5]) { cube([6,6,1], true); }
cylinder(d=6.5,h=0.5);

$fn=50;