import java.util.Random;
public class approxPiST{
	
	static int R = 1;
	static double inside;
	public static void main(String args[]){
		Random r = new Random();
		
		int nPoints = Integer.parseInt(args[0]);
			
		for(int i = 0; i<nPoints;i++){
			System.out.println(i);
			step(r);
		}
		
		System.out.println("Total Number of points: " + nPoints);
		System.out.println("Points within circle: " + inside);
		System.out.println("Pi estimation: " + 4*(inside/nPoints));		
		
	}
	
	public static void step(Random r){
		if(isInsideCircle(r.nextDouble(), r.nextDouble()))
				inside++;
	}
	
	
	private static boolean isInsideCircle(double x, double y){
		return x*x + y*y <= R;	
	}
}




