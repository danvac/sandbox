
dBW=101.5;
dBH=52;

ledW=101.5;
ledH=19.5;
ledD=8.5;
hdrH=21;
hdrW=9.5;

hdrD=21.5; //?
shD=8;

thickness = 13;

w = 1.8;
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

module shell(){
	for (b=[-1,0,1])
		translate([-d/2-trampTh/2-0.5,b*25,-standHeight/2+ledH/2+2])rotate([0,-6,0])cube([2.5,2,ledH+8],center=true);
	}
}

//shell();
ledP=69/7;
bP=62/7;

module ledBoard() {
	//board
	cube([dBW,1,dBH],center=true);
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
    translate([dBW/2-3,dBH/2-3,-2.5+shD/2]) screwhole();
    translate([-dBW/2+3,-dBH/2+3,-2.5+shD/2]) screwhole();
	translate([dBW/2-3,-dBH/2+3,-2.5+shD/2]) screwhole();
	
	
}

module screwhole(){
	difference(){
		cylinder(r=2.7,h=shD,center=true);
		cylinder(r=1,h=10,center=true);
	}
}


module ledSlot(){
	//LED slot
	ledBoard();
	//board
	translate([0,+2.5-10,0])cube([dBW+2*e,20,dBH+2*e],center=true);
}

$fn=50;