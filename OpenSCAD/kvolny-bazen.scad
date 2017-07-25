h = 83;
d = 17.5;
x = 12.5;
a = 0;

difference() {
  cylinder(d=d, h=h);
  //translate([x/2+10,0,h/2]) cube([20,20,h], true);
  translate([-x/2-10,0,h/2]) cube([20,20,h], true);
}
/*
rotate([0,a,0])
translate([0,0,h])
difference() {
  cylinder(d=d, h=h);
  //translate([x/2+10,0,h/2]) cube([20,20,h], true);
  translate([-x/2-10,0,h/2]) cube([20,20,h], true);
}*/