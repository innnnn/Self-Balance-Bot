#ifndef BALANCEBOTSTATEFEEDBACKCONTROLLER_H
#define BALANCEBOTSTATEFEEDBACKCONTROLLER_H

class BalanceBotStateFeedbackController{
  private:
  	float k1;
  	float k2;
  	float k3;
  	float k4;
  	
  public:
  	BalanceBotStateFeedbackController();
  	void SetK(k1, k2, k3, k4);
  	float Update(float psi, float pdid, float theta, float thetad);
};

#endif //BALANCEBOTSTATEFEEDBACKCONTROLLER_H
