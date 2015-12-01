
dBW=101.5;
dBH=52;

ledW=101.5;
ledH=19.5;
ledD=8.5;
hdrH=21;
hdrW=9.5;

hdrD=21.5; //?
shD=7.5;

thickness = 13.5;

w = 1.5;
t = 0.5;
e = 0.5;


case();


module base(){
difference(){
	union(){
		body();
		translate([-84,45,(hdrH+4)/2+2-dBH])cube([hdrD+4,hdrW+6,hdrH+4],center=true);
		translate([-84,-45,(hdrH+4)/2+2-dBH])cube([hdrD+4,hdrW+2,hdrH+4],center=true);
	}
	translate([-d/2+10, 0, -standHeight/2+0.9+2])rotate([0,0,90])ledSlot();
	translate([50,0,0])cube([200,200,200],center=true);
}
}

ledP=69/7;
bP=62/7;

module ledBoard() {
	//board
	//cube([dBW,1,dBH],center=true);
	//LED strip
	translate([0,5,dBH/2-ledH/2-6]) cube([ledW+t,ledD,ledH+t],center=true);
	//big header
	translate([dBW/2-hdrW/2,hdrD/2,-hdrH/2+t]) cube([hdrW+t,hdrD,hdrH],center=true);
	//little header
	translate([-dBW/2+hdrW/2,hdrD/2,-hdrH/2+t]) cube([hdrW+t,hdrD,hdrH],center=true);
	for (l=[1:8]){
		translate([-l*ledP+42.85,4,-9.5])rotate([90,0,0]) cylinder(r1=2.1,r2=5.1,h=10,center=true);
		translate([-l*bP+39.85,0,-20.5])rotate([90,0,0])cylinder(r=3,h=20,center=true);
	}
}


module case(){
	rotate([-90,0,0])difference(){
		translate([0,4-thickness/2,0])cube([dBW+2*w+2*e,thickness,dBH+2*w+2*e],center=true);
		ledSlot();
	}
	translate([-dBW/2+3,dBH/2-3,-2.5+shD/2]) screwhole();
    translate([dBW/2-3,dBH/2-3,-2.5+shD/2]) screwhole(270);
    translate([-dBW/2+3,-dBH/2+3,-2.5+shD/2]) screwhole(90);
	translate([dBW/2-3,-dBH/2+3,-2.5+shD/2]) screwhole(180);
	
	
}

module screwhole(rotation=0) {
	difference(){
        union() {
          rotate([0,0,rotation]) {
            translate([-1,0,0]) cube([7,2,shD],true);
            translate([0,1,0]) cube([2,7,shD],true);
          }
		  cylinder(r=2.7,h=shD,center=true);
        }
		cylinder(r=1.15,h=10,center=true);
	}
}


module ledSlot(){
	//LED slot
	ledBoard();
	//board
    lx = 72; ly = 1; lz = 10.5;
	translate([0,+2.5-10,0]) {
      difference() {
        cube([dBW+2*e,20,dBH+2*e],center=true);
        //translate([0,10-ly/2,-dBH/2+lz/2]) cube([lx,ly,lz],center=true);
      	for (l=[1:8]){
		  translate([-l*bP+39.85,10-ly/2,-20.5])rotate([90,0,0]) cylinder(r=4,h=ly,center=true);
	}

      }
    }
}

$fn=50;