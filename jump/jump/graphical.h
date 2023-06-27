class Graphical {
	private:
		double gx,gy,gz;
		float color[3];
		int num; //ͼ�α��

	public:
		Graphical();
		void theThree(double x, double z);
		double getGx();
		double getGz();
		void rectangle(); //���� 1
		void triangle();  //������ 4 
		void circular(); // Բ�� 3
		void square(); // ������ 2
		void positionRandom();
		void changeModel(Graphical* p);
		static void exchange(Graphical* p, Graphical* q);
		int build();
};
