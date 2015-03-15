#include <iostream>
#include <iomanip> // pour setfill
#include <string>
#include <vector>
using namespace std;

typedef string Day; // type pour définir les jous

void print_time(double); // fonction utile pour afficher les heures

class Time
/* Représente le jour et l'heure d'un évènement.
 * Les heures sont représentées en double depuis minuit.
 * Par exemple 14:30 est représenté 14.5.
 * La fonction-outil print_time permet d'afficher de telles heures.
 */
{
public:
  // Constructeur à partir du jour et de l'heure
  Time(Day jour, double heure)
    : day_(jour), hour_(heure) {
  }

  // Affichage
  void print() const {
    cout << day_ << " à ";
    print_time(hour_);
  }

  // Pour connaître le jour
  Day day() const {
    return day_;
  }

  // Pour connaître l'heure
  double hour() const {
    return hour_;
  }

private:
  Day day_;
  double hour_;
};

/* Fonction outil pour afficher les temps représentés en double
 * comme indiqué ci-dessus.
 */
void print_time(double t)
{
  cout << setfill('0') << setw(2) << int(t)
       << setfill('0') << setw(1) << ":"
       << setfill('0') << setw(2) << int(60.0 * (t - int(t)));
}

/* Type utilisé pour identifier les cours.
 * Chaque cours aura en effet un identificateur unique ; par exemple "CS-101".
 */
typedef string CourseId;

/*******************************************
 * Complétez le programme à partir d'ici.
 *******************************************/

class Activity {

private:
	string location;
	double st;
	double duration;
	Time start;
	int convertToMinutes(double t) const {
		int minutes = (int(t) * 60) + int(60.0 * (t - int(t)));
		return minutes;
	}


public:
	Activity (string loc,Day da,double st,double dur):location(loc),start(da,dur) {};
	Activity (const Activity& other) = delete;
	string getLocation (void) {return location;}
	Time getTime (void) {return start;}
	double getDuration (void) const {return duration;}
	bool conflicts (const Activity& other) const {

		int x1=convertToMinutes(start.hour());
		int x2=convertToMinutes(start.hour()+getDuration());
		int y1=convertToMinutes(other.start.hour());
		int y2=convertToMinutes(other.start.hour()+other.getDuration());

	//	if (start.day()==other.start.day() && start.hour() < other.start.hour() && start.hour() + duration > other.start.hour()) return false;
		if (start.day()==other.start.day() && x1 <= y2 && y1 < x2) return true;
		else return false; 	
	}

	void print() const {
		cout << " le " ;
		start.print() ;
		cout << " en " << location <<  ", durée " ;
		print_time(duration); 
		cout << endl;
	
	}
};

class Course {

private:
	CourseId cid;
	string crs;
	const Activity& lecture;
	const Activity& session;
	int credit;

public:
	Course (CourseId cd, string nm, const Activity& le, const Activity& se, int cr):cid(cd),crs(nm),lecture(le),session(se) {
		cout << "Nouveau cours : " << cid << endl;
	}

	~Course () {
		cout << "Suppression du cours : " << cid << endl;
	}


	Course (const Course& other) = delete;
    CourseId getId (void) const {return cid;}
    string getTitle (void) const {return crs;}
    int getCredits (void) const {return credit;}

    double workload (void) const {
        double tot=lecture.getDuration()+session.getDuration();
        return tot;
    }

    void print() const {
        cout << getId() << ":" << getTitle() << " - cours ";
        lecture.print();
        cout << ", exercices ";
        session.print();
        cout << ". crédits : " << getCredits() << endl;
    }

    bool conflicts (const Activity& other) const {
       return (lecture.conflicts(other) || session.conflicts(other));
    }

    bool conflicts (const Course& other) const {
        return (lecture.conflicts(other.lecture) || lecture.conflicts(other.session) || session.conflicts(other.lecture) || session.conflicts(other.session));
    }
};

class StudyPlan {

private:
	vector <const Course*> cvec;

	const Course* findcourse (const CourseId& cid) {
		const Course * temp=nullptr;
		for (vector<const Course*>::iterator it = cvec.begin() ; it != cvec.end(); ++it) 
    		if ((*it)->getId() == cid) temp = *it;
		return temp;
	}


public:
	StudyPlan() {};
	~StudyPlan () {
		for(vector <const Course*>::const_iterator it = cvec.begin(); it != cvec.end(); it++){
    		delete *it;
    	}
		cvec.clear();
	}

	void add_course(const Course& c) {
		cvec.push_back(&c);
	}

	bool conflicts (const CourseId& c, vector <CourseId>& myvec) {
		const Course* t1=findcourse(c);
		if (t1 == nullptr) return false;
		else {
			for (vector<CourseId>::iterator it = myvec.begin() ; it != myvec.end(); ++it) {
				const Course* t2=findcourse(*it);
				if (t1->conflicts(*t2)) return true;
    		}
    		return false;
		}
	}

    void print(const CourseId& cid) {
    	const Course* t1=findcourse(cid);
    	if (t1)
	    	t1->print();
    }

	int credits (const CourseId& cid) {
		const Course* t1=findcourse(cid);
		if (t1) return t1->getCredits();
		else return 0;
    }

	double workload (const CourseId& cid) {
		const Course* t1=findcourse(cid);
		if (t1) return t1->workload();
		else return 0;
    }

    void printCourseSuggestions (vector <CourseId>& myvec) {
    	int n=0;
		for (vector<CourseId>::iterator it1 = myvec.begin() ; it1 != myvec.end(); ++it1) {
			const Course* t1=findcourse(*it1);
			if (t1 != nullptr) {
				for (vector<const Course*>::iterator it2 = cvec.begin() ; it2 != cvec.end(); ++it2) {
					if ((*it2)->getId() != t1->getId()) {
						if (!(*it2)->conflicts(*t1)) {
							(*it2)->print();
							cout << endl;
						}
						else
							n++;
					}
				}
			}
    	}
    	if (n != 0)
    		cout << "Aucun cours n'est compatible avec la sélection de cours." << endl;
    }
};

class Schedule {

private:
	vector <CourseId> civec;
	const StudyPlan& sp;

public:
	Schedule(const StudyPlan& plan):sp(plan) {}; 
	bool add_course(const CourseId& cid) {
		for (vector<CourseId>::iterator it1 = civec.begin() ; it1 != civec.end(); ++it1) {
			if (cid.)
	}

	double computeDailyWorkload () {
		for (vector<CourseId>::iterator it1 = civec.begin() ; it1 != civec.end(); ++it1) {
			
		}
	}
};



    //cout << ", durée ";


    //cout << ". crédits : ";


      //cout << "Aucun cours n'est compatible avec la sélection de cours." << endl;


    //cout << "Total de crédits   : ";
    //cout << "Charge journalière : ";
    //cout << "Suggestions :" << endl;


/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

int main()
{
  // Quelques activités
  Activity physicsLecture  ("Central Hall", "lundi",  9.25, 1.75);
  Activity physicsExercises("Central 101" , "lundi", 14.00, 2.00);

  Activity historyLecture  ("North Hall", "lundi", 10.25, 1.75);
  Activity historyExercises("East 201"  , "mardi",  9.00, 2.00);

  Activity financeLecture  ("South Hall",  "vendredi", 14.00, 2.00);
  Activity financeExercises("Central 105", "vendredi", 16.00, 1.00);

  // On affiche quelques informations sur ces activités
  cout << "L'activité physicsLecture a lieu ";
  physicsLecture.print();
  cout << "." << endl;

  cout << "L'activité historyLecture a lieu ";
  historyLecture.print();
  cout << "." << endl;

  if (physicsLecture.conflicts(historyLecture)) {
    cout << "physicsLecture est en conflit avec historyLecture."
         << endl;
  } else {
    cout << "physicsLecture n'est pas en conflit avec historyLecture."
         << endl;
  }
  cout << endl;

  // Création d'un plan d'étude
  StudyPlan studyPlan;
  Course physics("PHY-101", "Physique", physicsLecture, physicsExercises, 4);
  studyPlan.add_course(physics);
  Course history("HIS-101", "Histoire", historyLecture, historyExercises, 4);
  studyPlan.add_course(history);
  Course finance("ECN-214", "Finance" , financeLecture, financeExercises, 3);
  studyPlan.add_course(finance);

  // Première tentative d'emploi du temps
  Schedule schedule1(studyPlan);
  schedule1.add_course(finance.getId());
  cout << "Emploi du temps 1 :" << endl;
  schedule1.print();

  /* On ne sait pas encore très bien quoi faire : on essaye donc
   * sur une copie de l'emploi du temps précédent.
   */
  Schedule schedule2(schedule1);
  schedule2.add_course(history.getId());
  cout << "Emploi du temps 2 :" << endl;
  schedule2.print();

  // Un troisième essai
  Schedule schedule3(studyPlan);
  schedule3.add_course(physics.getId());
  cout << "Emploi du temps 3 :" << endl;
  schedule3.print();

  return 0;
}
