#ifndef AttMedHelpers_h
#define AttMedHelpers_h

class AttMedHelpers {
  private:
    int recentAttentionVal1 = 0;
    int recentAttentionVal2 = 0;
    int recentAttentionVal3 = 0;

    int recentMeditationVal1 = 0;
    int recentMeditationVal2 = 0;
    int recentMeditationVal3 = 0;

  public:
    AttMedHelpers();

    void updateRecentAttentionVals(int newVal);
    void updateRecentMeditationVals(int newVal);

    double calculateRecentAttentionAvg();
    double calculateRecentMeditationAvg();
};

#endif
