
// AirportGUIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AirportGUI.h"
#include "AirportGUIDlg.h"
#include "afxdialogex.h"
#include <vector>
#include <ctime>
#include <cmath>
#include <random>
#include <queue>

#include "Airplane.h"
#include "Airport.h"
#include "Event.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int NumberPlanes = 1000;
int NumberAirports = 100;

double CurrentTime = 0.0;
double SimulationTime = 200.0;
vector<vector<double> > distanceMatrix(100, vector<double>(100));

CString results;

void handle(vector<vector<double> > distanceMatrix, Event* event, std::vector<Airport*> AirportArray, std::priority_queue<Event*, std::vector<Event*>, CompareTime> &pq);
int getInitialAirport();
string process();


CAirportGUIDlg::CAirportGUIDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAirportGUIDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAirportGUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAirportGUIDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CAirportGUIDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CAirportGUIDlg message handlers

BOOL CAirportGUIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAirportGUIDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAirportGUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CAirportGUIDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	CEdit* pMessage;
	CString str;

	pMessage = (CEdit*)GetDlgItem(IDC_PLANE);
	pMessage->GetWindowTextW(str);
	NumberPlanes = _tstoi(LPCTSTR(str));

	pMessage = (CEdit*)GetDlgItem(IDC_TIME);
	pMessage->GetWindowTextW(str);
	SimulationTime = _tstof(LPCTSTR(str));

	results = "";

	// process
	int initialIndex;
	srand(time(NULL));

	// Set up the distance matrix between 50 airports
	for (int i = 0; i < NumberAirports; ++i) {
		for (int j = 0; j<NumberAirports; ++j){
			if (i == j)
				distanceMatrix[i][j] = 0.0;
			if (i < j)
				distanceMatrix[i][j] = (double)(2000 + ((rand() % (2000 - 1)) + 1));
			if (i > j)
				distanceMatrix[i][j] = 0.0;
		}
	}
	for (int i = 0; i < NumberAirports; ++i) {
		for (int j = 0; j < NumberAirports; ++j){
			if (i > j)
				distanceMatrix[i][j] = distanceMatrix[j][i];
		}
	}


	// Set up the priority queue and 50 airports
	std::priority_queue<Event*, std::vector<Event*>, CompareTime> pq;

	// Set the first type of airport - Required time = 240, Runway = 4

	Airport* clt = new Airport("CLT", 15.0, 240.0, 15.0, 0, 0, 4);
	Airport* ind = new Airport("IND", 15.0, 240.0, 15.0, 0, 1, 4);
	Airport* bos = new Airport("BOS", 15.0, 240.0, 15.0, 0, 2, 4);
	Airport* lhr = new Airport("LHR", 15.0, 240.0, 15.0, 0, 3, 4);
	Airport* hnd = new Airport("HND", 15.0, 240.0, 15.0, 0, 4, 4);

	Airport* sin = new Airport("SIN", 15.0, 240.0, 15.0, 0, 5, 4);
	Airport* hkg = new Airport("HKG", 15.0, 240.0, 15.0, 0, 6, 4);
	Airport* dbx = new Airport("DBX", 15.0, 240.0, 15.0, 0, 7, 4);
	Airport* atl = new Airport("ATL", 15.0, 240.0, 15.0, 0, 8, 4);
	Airport* icn = new Airport("ICN", 15.0, 240.0, 15.0, 0, 9, 4);

	Airport* pek = new Airport("PEK", 15.0, 240.0, 15.0, 0, 10, 4);
	Airport* cdg = new Airport("CDG", 15.0, 240.0, 15.0, 0, 11, 4);
	Airport* lax = new Airport("LAX", 15.0, 240.0, 15.0, 0, 12, 4);
	Airport* muc = new Airport("MUC", 15.0, 240.0, 15.0, 0, 13, 4);
	Airport* ord = new Airport("ORD", 15.0, 240.0, 15.0, 0, 14, 4);

	Airport* dfw = new Airport("DFW", 15.0, 240.0, 15.0, 0, 15, 4);
	Airport* ams = new Airport("AMS", 15.0, 240.0, 15.0, 0, 16, 4);
	Airport* fra = new Airport("FRA", 15.0, 240.0, 15.0, 0, 17, 4);
	Airport* zrh = new Airport("ZRH", 15.0, 240.0, 15.0, 0, 18, 4);
	Airport* jfk = new Airport("JFK", 15.0, 240.0, 15.0, 0, 19, 4);

	// Set the second type of airport - Required time = 180, Runway = 3

	Airport* kix = new Airport("KIX", 15.0, 180.0, 15.0, 0, 20, 3);
	Airport* pvg = new Airport("PVG", 15.0, 180.0, 15.0, 0, 21, 3);
	Airport* nrt = new Airport("NRT", 15.0, 180.0, 15.0, 0, 22, 3);
	Airport* ngo = new Airport("NGO", 15.0, 180.0, 15.0, 0, 23, 3);
	Airport* yvr = new Airport("YVR", 15.0, 180.0, 15.0, 0, 24, 3);

	Airport* tpe = new Airport("TPE", 15.0, 180.0, 15.0, 0, 25, 3);
	Airport* bkk = new Airport("BKK", 15.0, 180.0, 15.0, 0, 26, 3);
	Airport* mad = new Airport("MAD", 15.0, 180.0, 15.0, 0, 27, 3);
	Airport* den = new Airport("DEN", 15.0, 180.0, 15.0, 0, 28, 3);
	Airport* kul = new Airport("KUL", 15.0, 180.0, 15.0, 0, 29, 3);

	Airport* ist = new Airport("IST", 15.0, 180.0, 15.0, 0, 30, 3);
	Airport* lgw = new Airport("LGW", 15.0, 180.0, 15.0, 0, 31, 3);
	Airport* hel = new Airport("HEL", 15.0, 180.0, 15.0, 0, 32, 3);
	Airport* lga = new Airport("LGA", 15.0, 180.0, 15.0, 0, 33, 3);
	Airport* cph = new Airport("CPH", 15.0, 180.0, 15.0, 0, 34, 3);

	Airport* doh = new Airport("DOH", 15.0, 180.0, 15.0, 0, 35, 3);
	Airport* syd = new Airport("SYD", 15.0, 180.0, 15.0, 0, 36, 3);
	Airport* las = new Airport("LAS", 15.0, 180.0, 15.0, 0, 37, 3);
	Airport* msp = new Airport("MSP", 15.0, 180.0, 15.0, 0, 38, 3);
	Airport* sha = new Airport("SHA", 15.0, 180.0, 15.0, 0, 39, 3);

	// Set the third type of airport - Required time = 120, Runway = 2

	Airport* cgk = new Airport("CGK", 15.0, 120.0, 15.0, 0, 40, 2);
	Airport* yyz = new Airport("YYZ", 15.0, 120.0, 15.0, 0, 41, 2);
	Airport* sfo = new Airport("SFO", 15.0, 120.0, 15.0, 0, 42, 2);
	Airport* gru = new Airport("GRU", 15.0, 120.0, 15.0, 0, 43, 2);
	Airport* sea = new Airport("SEA", 15.0, 120.0, 15.0, 0, 44, 2);

	Airport* iah = new Airport("IAH", 15.0, 120.0, 15.0, 0, 45, 2);
	Airport* ktm = new Airport("KTM", 15.0, 120.0, 15.0, 0, 46, 2);
	Airport* can = new Airport("CAN", 15.0, 120.0, 15.0, 0, 47, 2);
	Airport* ewr = new Airport("EWR", 15.0, 120.0, 15.0, 0, 48, 2);
	Airport* bcn = new Airport("BCN", 15.0, 120.0, 15.0, 0, 49, 2);

	Airport* bis = new Airport("BIS", 15.0, 120.0, 15.0, 0, 52, 2);
	Airport* gpt = new Airport("GPT", 15.0, 120.0, 15.0, 0, 53, 2);
	Airport* bhm = new Airport("BHM", 15.0, 120.0, 15.0, 0, 54, 2);
	Airport* boi = new Airport("BOI", 15.0, 120.0, 15.0, 0, 55, 2);
	Airport* bwg = new Airport("BWG", 15.0, 120.0, 15.0, 0, 56, 2);

	Airport* xhh = new Airport("XHH", 15.0, 120.0, 15.0, 0, 57, 2);
	Airport* bzn = new Airport("BZN", 15.0, 120.0, 15.0, 0, 58, 2);
	Airport* qkb = new Airport("QKB", 15.0, 120.0, 15.0, 0, 59, 2);
	Airport* rbh = new Airport("RBH", 15.0, 120.0, 15.0, 0, 60, 2);
	Airport* buf = new Airport("BUF", 15.0, 120.0, 15.0, 0, 61, 2);

	Airport* ifp = new Airport("IFP", 15.0, 120.0, 15.0, 0, 62, 2);
	Airport* btm = new Airport("BTM", 15.0, 120.0, 15.0, 0, 63, 2);
	Airport* cys = new Airport("CYS", 15.0, 120.0, 15.0, 0, 64, 2);
	Airport* ckx = new Airport("CKX", 15.0, 120.0, 15.0, 0, 65, 2);
	Airport* cic = new Airport("CIC", 15.0, 120.0, 15.0, 0, 66, 2);

	Airport* vak = new Airport("VAK", 15.0, 120.0, 15.0, 0, 67, 2);
	Airport* irc = new Airport("IRC", 15.0, 120.0, 15.0, 0, 68, 2);
	Airport* cod = new Airport("COD", 15.0, 120.0, 15.0, 0, 69, 2);
	Airport* cle = new Airport("CLE", 15.0, 120.0, 15.0, 0, 70, 2);
	Airport* pie = new Airport("PIE", 15.0, 120.0, 15.0, 0, 71, 2);

	// Set the forth type of airport - Required time = 60, Runway = 1

	Airport* cvn = new Airport("CVN", 15.0, 60.0, 15.0, 0, 72, 1);
	Airport* cho = new Airport("CHO", 15.0, 60.0, 15.0, 0, 73, 1);
	Airport* dsm = new Airport("DSM", 15.0, 60.0, 15.0, 0, 74, 1);
	Airport* dik = new Airport("DIK", 15.0, 60.0, 15.0, 0, 75, 1);
	Airport* ddc = new Airport("DDC", 15.0, 60.0, 15.0, 0, 76, 1);

	Airport* duj = new Airport("DUJ", 15.0, 60.0, 15.0, 0, 77, 1);
	Airport* dbq = new Airport("DBQ", 15.0, 60.0, 15.0, 0, 78, 1);
	Airport* dro = new Airport("DRO", 15.0, 60.0, 15.0, 0, 79, 1);
	Airport* abe = new Airport("ABE", 15.0, 60.0, 15.0, 0, 80, 1);
	Airport* eli = new Airport("ELI", 15.0, 60.0, 15.0, 0, 81, 1);

	Airport* eek = new Airport("EEK", 15.0, 60.0, 15.0, 0, 82, 1);
	Airport* lyu = new Airport("LYU", 15.0, 60.0, 15.0, 0, 83, 1);
	Airport* elm = new Airport("ELM", 15.0, 60.0, 15.0, 0, 84, 1);
	Airport* esc = new Airport("ESC", 15.0, 60.0, 15.0, 0, 85, 1);
	Airport* wdg = new Airport("WDG", 15.0, 60.0, 15.0, 0, 86, 1);

	Airport* flg = new Airport("FLG", 15.0, 60.0, 15.0, 0, 87, 1);
	Airport* qwf = new Airport("QWF", 15.0, 60.0, 15.0, 0, 88, 1);
	Airport* tbn = new Airport("TBN", 15.0, 60.0, 15.0, 0, 89, 1);
	Airport* fat = new Airport("FAT", 15.0, 60.0, 15.0, 0, 90, 1);
	Airport* gup = new Airport("GUP", 15.0, 60.0, 15.0, 0, 91, 1);

	Airport* ggg = new Airport("GGG", 15.0, 60.0, 15.0, 0, 92, 1);
	Airport* jgc = new Airport("JGC", 15.0, 60.0, 15.0, 0, 93, 1);
	Airport* gjt = new Airport("GJT", 15.0, 60.0, 15.0, 0, 94, 1);
	Airport* kdi = new Airport("KDI", 15.0, 60.0, 15.0, 0, 95, 1);
	Airport* gtf = new Airport("GTF", 15.0, 60.0, 15.0, 0, 96, 1);

	Airport* jrg = new Airport("HRG", 15.0, 60.0, 15.0, 0, 97, 1);
	Airport* hdn = new Airport("HDN", 15.0, 60.0, 15.0, 0, 98, 1);
	Airport* avl = new Airport("AVL", 15.0, 60.0, 15.0, 0, 99, 1);
	Airport* auh = new Airport("AUH", 15.0, 60.0, 15.0, 0, 50, 1);
	Airport* kbc = new Airport("KBC", 15.0, 60.0, 15.0, 0, 51, 1);


	vector<Airport*> AirportArray;
	vector<Airplane*> AirplaneArray;


	// Type 1
	AirportArray.push_back(clt);
	AirportArray.push_back(ind);
	AirportArray.push_back(bos);
	AirportArray.push_back(lhr);
	AirportArray.push_back(hnd);

	AirportArray.push_back(sin);
	AirportArray.push_back(hkg);
	AirportArray.push_back(dbx);
	AirportArray.push_back(atl);
	AirportArray.push_back(icn);

	AirportArray.push_back(pek);
	AirportArray.push_back(cdg);
	AirportArray.push_back(lax);
	AirportArray.push_back(muc);
	AirportArray.push_back(ord);

	AirportArray.push_back(dfw);
	AirportArray.push_back(ams);
	AirportArray.push_back(fra);
	AirportArray.push_back(zrh);
	AirportArray.push_back(jfk);

	// Type 2
	AirportArray.push_back(kix);
	AirportArray.push_back(pvg);
	AirportArray.push_back(nrt);
	AirportArray.push_back(ngo);
	AirportArray.push_back(yvr);

	AirportArray.push_back(tpe);
	AirportArray.push_back(bkk);
	AirportArray.push_back(mad);
	AirportArray.push_back(den);
	AirportArray.push_back(kul);

	AirportArray.push_back(ist);
	AirportArray.push_back(lgw);
	AirportArray.push_back(hel);
	AirportArray.push_back(lga);
	AirportArray.push_back(cph);

	AirportArray.push_back(doh);
	AirportArray.push_back(syd);
	AirportArray.push_back(las);
	AirportArray.push_back(msp);
	AirportArray.push_back(sha);

	// Type 3
	AirportArray.push_back(cgk);
	AirportArray.push_back(yyz);
	AirportArray.push_back(sfo);
	AirportArray.push_back(gru);
	AirportArray.push_back(sea);

	AirportArray.push_back(iah);
	AirportArray.push_back(ktm);
	AirportArray.push_back(can);
	AirportArray.push_back(ewr);
	AirportArray.push_back(bcn);

	AirportArray.push_back(bis);
	AirportArray.push_back(gpt);
	AirportArray.push_back(bhm);
	AirportArray.push_back(boi);
	AirportArray.push_back(bwg);

	AirportArray.push_back(xhh);
	AirportArray.push_back(bzn);
	AirportArray.push_back(qkb);
	AirportArray.push_back(rbh);
	AirportArray.push_back(buf);

	AirportArray.push_back(ifp);
	AirportArray.push_back(btm);
	AirportArray.push_back(cys);
	AirportArray.push_back(ckx);
	AirportArray.push_back(cic);

	AirportArray.push_back(vak);
	AirportArray.push_back(irc);
	AirportArray.push_back(cod);
	AirportArray.push_back(cle);
	AirportArray.push_back(pie);

	// Type 4
	AirportArray.push_back(cvn);
	AirportArray.push_back(cho);
	AirportArray.push_back(dsm);
	AirportArray.push_back(dik);
	AirportArray.push_back(ddc);

	AirportArray.push_back(duj);
	AirportArray.push_back(dbq);
	AirportArray.push_back(dro);
	AirportArray.push_back(abe);
	AirportArray.push_back(eli);

	AirportArray.push_back(eek);
	AirportArray.push_back(lyu);
	AirportArray.push_back(elm);
	AirportArray.push_back(esc);
	AirportArray.push_back(wdg);

	AirportArray.push_back(flg);
	AirportArray.push_back(qwf);
	AirportArray.push_back(tbn);
	AirportArray.push_back(fat);
	AirportArray.push_back(gup);

	AirportArray.push_back(ggg);
	AirportArray.push_back(jgc);
	AirportArray.push_back(gjt);
	AirportArray.push_back(kdi);
	AirportArray.push_back(gtf);

	AirportArray.push_back(jrg);
	AirportArray.push_back(hdn);
	AirportArray.push_back(avl);
	AirportArray.push_back(auh);
	AirportArray.push_back(kbc);



	// Set up 1000 airplanes with five categories of speed and maximum number of passengers
	for (int i = 0; i < NumberPlanes*0.2; ++i){
		string s = to_string(i);
		Airplane *airplane = new Airplane("A380_" + s, i, 0, 1, 0.0, 9.45, 500);
		AirplaneArray.push_back(airplane);
	}

	for (int i = NumberPlanes*0.2; i < NumberPlanes*0.4; ++i){
		string s = to_string(i);
		Airplane *airplane = new Airplane("BO747_" + s, i, 0, 1, 0.0, 9.50, 400);
		AirplaneArray.push_back(airplane);
	}
	for (int i = NumberPlanes*0.4; i < NumberPlanes*0.7; ++i){
		string s = to_string(i);
		Airplane *airplane = new Airplane("A330_" + s, i, 0, 1, 0.0, 9.00, 300);
		AirplaneArray.push_back(airplane);
	}

	for (int i = NumberPlanes*0.7; i < NumberPlanes; ++i){
		string s = to_string(i);
		Airplane *airplane = new Airplane("BO787_" + s, i, 0, 1, 0.0, 9.35, 250);
		AirplaneArray.push_back(airplane);
	}


	// Randomly initialize the initial airport for each airplane
	Event* event;
	for (int i = 0; i < NumberPlanes; ++i){
		initialIndex = rand() % NumberAirports;

		event = new Event(0, AirportArray[initialIndex], 0, AirportArray[1]);
		event->setPlaneInformation(AirplaneArray[i]);

		pq.push(event);

	}



	// Run the simulation program until timestamp reaches the simulation time
	while (CurrentTime < SimulationTime && pq.empty() == false){

		handle(distanceMatrix, pq.top(), AirportArray, pq);
		pq.pop();

	}

	for (int j = 0; j < NumberAirports; ++j){

		cout << "Total circling time is: " << AirportArray[j]->getCirclingTime() << " from airport " << AirportArray[j]->getName() << endl;
		cout << "Average circling time is: " << AirportArray[j]->getCirclingTime() / (double)AirportArray[j]->getAirplaneNumber() << " from airport " << AirportArray[j]->getName() << endl;
		cout << "Total arriving passenger is: " << AirportArray[j]->getArrivePassenger() << " from airport " << AirportArray[j]->getName() << endl;
		cout << "Total departing passenger is: " << AirportArray[j]->getDepartPassenger() << " from airport " << AirportArray[j]->getName() << endl;

		CString tmp;
		tmp.Format(_T("Total circling time is: %.4f from airport "), AirportArray[j]->getCirclingTime());
		string tmp2 = AirportArray[j]->getName();
		tmp += tmp2.c_str();
		tmp += "\r\n";
		results += tmp;

		tmp.Format(_T("Average circling time is: %.4f from airport "), AirportArray[j]->getCirclingTime() / (double)AirportArray[j]->getAirplaneNumber());
		tmp2 = AirportArray[j]->getName();
		tmp += tmp2.c_str();
		tmp += "\r\n";
		results += tmp;

		tmp.Format(_T("Total arriving passenger is: %d  from airport "), AirportArray[j]->getArrivePassenger());
		tmp2 = AirportArray[j]->getName();
		tmp += tmp2.c_str();
		tmp += "\r\n";
		results += tmp;

		tmp.Format(_T("Total departing passenger is: %d  from airport "), AirportArray[j]->getDepartPassenger());
		tmp2 = AirportArray[j]->getName();
		tmp += tmp2.c_str();
		tmp += "\r\n";
		results += tmp;

	}
	
	pMessage = (CEdit*)GetDlgItem(IDC_RESULT);
	pMessage->SetWindowTextW(results);
}


int getInitialAirport() {
	int randomNumber = rand() % NumberAirports;
	cout << randomNumber << rand() << endl;
	return randomNumber;
}



void handle(vector<vector<double> > distanceMatrix, Event* event, std::vector<Airport*> AirportArray, std::priority_queue<Event*, std::vector<Event*>, CompareTime> &pq){
	int random_number;
	Event* airEvent = new Event();
	airEvent = event;
	Airplane* airplane1 = airEvent->getPlaneInformation();
	Airport* CurrentAirport = airEvent->getHandler();

	CurrentTime = airEvent->getTime();


	// Case 0 is arriving event, case 1 is landed event, case 2 is takeoff event, and case 3 is departing event
	switch (airEvent->getType()) {
	case 0: //arriving event

	{
		CurrentAirport->m_numberOfPlanes++;
		cout << CurrentTime << ": Plane " << airplane1->getName() << " arrived at airport " << CurrentAirport->getName() << endl;
		airplane1->setArrivalTime(CurrentTime);  // store the arrival time for the plane

		CString tmp;
		tmp.Format(_T("%.2f: "), CurrentTime);
		string tmp2 = "Plane " + airplane1->getName() + " arrived at airport " + CurrentAirport->getName();
		tmp += tmp2.c_str();
		tmp += "\r\n";
		results += tmp;

		random_number = 1 + (rand() % (int)(1000 - 1 + 1));


		/* if there is no plane waiting to land and the runway is free, schedule a landed event for this plane
		otherwise push the event into arrival_Queue */
		if (CurrentAirport->ArrivingQueue.empty() == true && CurrentAirport->EmergencyQueue.empty() == true) {
			if (CurrentAirport->checkFree()) {
				Event* landedEvent = new Event(CurrentAirport->m_runwayTimeToLand + CurrentTime, CurrentAirport, event->PLANE_LANDED, airEvent->getPlaneDestination());
				landedEvent->setPlaneInformation(airplane1);
				pq.push(landedEvent);
				CurrentAirport->occupyRunway();
				CurrentAirport->setCirclingTime(CurrentTime - airplane1->getArrivalTime());
			}
			else {
				if (random_number == 10){
					CurrentAirport->EmergencyQueue.push(airEvent);
				}
				else {
					CurrentAirport->ArrivingQueue.push(airEvent);
				}
			}
		}
		else {
			if (random_number == 10){
				CurrentAirport->EmergencyQueue.push(airEvent);
			}
			else {
				CurrentAirport->ArrivingQueue.push(airEvent);
			}
		}


		break;
	}



	case 1:
	{
		//m_inTheAir--;
		//m_onTheGround++;
		CurrentAirport->setArrivePassenger(airplane1->getPassengerNumber());// calculate the number of passengers arriving that airport
		cout << CurrentTime << ": Plane " << airplane1->getName() << " lands at airport " << CurrentAirport->getName() << endl;

		CString tmp;
		tmp.Format(_T("%.2f: "), CurrentTime);
		string tmp2 = "Plane " + airplane1->getName() + " lands at airport " + CurrentAirport->getName();
		tmp += tmp2.c_str();
		tmp += "\r\n";
		results += tmp;

		// schedule a takeoff event for this airplane
		Event* takeoffEvent = new Event(CurrentAirport->m_requiredTimeOnGround + CurrentTime, CurrentAirport, event->PLANE_TAKEOFF, airEvent->getPlaneDestination());
		takeoffEvent->setPlaneInformation(airplane1);
		pq.push(takeoffEvent);



		if (CurrentAirport->EmergencyQueue.empty() == false) {
			Event* eEvent = CurrentAirport->EmergencyQueue.top();
			Event* elandedEvent = new Event(CurrentAirport->m_runwayTimeToLand + CurrentTime, CurrentAirport, event->PLANE_LANDED, eEvent->getPlaneDestination());
			elandedEvent->setPlaneInformation(eEvent->getPlaneInformation());
			pq.push(elandedEvent);
			CurrentAirport->setCirclingTime(CurrentTime - eEvent->getPlaneInformation()->getArrivalTime());
			CurrentAirport->EmergencyQueue.pop();
		}
		else {

			// if there is no airplane waiting to land, schedule an airplane to take off
			if (CurrentAirport->ArrivingQueue.empty() == true && CurrentAirport->TakingoffQueue.empty() == false) {
				Event* bEvent = CurrentAirport->TakingoffQueue.top();
				Event* departEvent = new Event(CurrentAirport->m_takeoffTime + CurrentTime, CurrentAirport, event->PLANE_DEPARTS, bEvent->getPlaneDestination());
				departEvent->setPlaneInformation(bEvent->getPlaneInformation());
				pq.push(departEvent);
				CurrentAirport->TakingoffQueue.pop();
			}
			// if there is no airplane waiting to take off, schedule an airplane to land
			else if (CurrentAirport->ArrivingQueue.empty() == false && CurrentAirport->TakingoffQueue.empty() == true) {
				Event* aEvent = CurrentAirport->ArrivingQueue.top();
				Event* landedEvent = new Event(CurrentAirport->m_runwayTimeToLand + CurrentTime, CurrentAirport, event->PLANE_LANDED, aEvent->getPlaneDestination());
				landedEvent->setPlaneInformation(aEvent->getPlaneInformation());
				pq.push(landedEvent);
				CurrentAirport->setCirclingTime(CurrentTime - aEvent->getPlaneInformation()->getArrivalTime());
				CurrentAirport->ArrivingQueue.pop();
			}
			else if (CurrentAirport->ArrivingQueue.empty() == true && CurrentAirport->TakingoffQueue.empty() == true) {
				CurrentAirport->freeRunway();
			}

			// if there are airplanes waiting to land and take off, compare their timestamps
			else {
				if (CurrentAirport->ArrivingQueue.top()->getTime() < CurrentAirport->TakingoffQueue.top()->getTime()) {
					Event* aEvent1 = CurrentAirport->ArrivingQueue.top();
					Event* landedEvent1 = new Event(CurrentAirport->m_runwayTimeToLand + CurrentTime, CurrentAirport, event->PLANE_LANDED, aEvent1->getPlaneDestination());
					landedEvent1->setPlaneInformation(aEvent1->getPlaneInformation());
					pq.push(landedEvent1);
					CurrentAirport->setCirclingTime(CurrentTime - aEvent1->getPlaneInformation()->getArrivalTime());
					CurrentAirport->ArrivingQueue.pop();
				}
				else {
					Event* bEvent1 = CurrentAirport->TakingoffQueue.top();
					Event* departEvent1 = new Event(CurrentAirport->m_takeoffTime + CurrentTime, CurrentAirport, event->PLANE_DEPARTS, bEvent1->getPlaneDestination());
					departEvent1->setPlaneInformation(bEvent1->getPlaneInformation());
					pq.push(departEvent1);
					CurrentAirport->TakingoffQueue.pop();

				}
			}

		}

		break;
	}



	case 2:
	{
		cout << CurrentTime << ": Plane " << airplane1->getName() << " takes off from airport " << CurrentAirport->getName() << endl;

		CString tmp;
		tmp.Format(_T("%.2f: "), CurrentTime);
		string tmp2 = "Plane " + airplane1->getName() + " takes off from airport " + CurrentAirport->getName();
		tmp += tmp2.c_str();
		tmp += "\r\n";
		results += tmp;

		/* if there is no plane waiting to take off and the runway is free, schedule a departure event for this plane
		otherwise push the event into takeoff_Queue */
		if (CurrentAirport->TakingoffQueue.empty() == true) {
			if (CurrentAirport->checkFree()) {
				Event* departEvent = new Event(CurrentAirport->m_takeoffTime + CurrentTime, CurrentAirport, event->PLANE_DEPARTS, airEvent->getPlaneDestination());
				departEvent->setPlaneInformation(airplane1);
				pq.push(departEvent);
				CurrentAirport->occupyRunway();
			}
			else {
				CurrentAirport->TakingoffQueue.push(airEvent);
			}
		}
		else {
			CurrentAirport->TakingoffQueue.push(airEvent);
		}

		break;
	}



	case 3:
	{
		//m_onTheGround--;
		airplane1->generatePassengerNumber();
		CurrentAirport->setDepartPassenger(airplane1->getPassengerNumber());
		cout << CurrentTime << ": Plane " << airplane1->getName() << " departs from airport " << CurrentAirport->getName() << endl;
		//System->out->println("Total departing passenger is: " + this->m_passenger_depart + " at airport " + m_airportName);

		CString tmp;
		tmp.Format(_T("%.2f: "), CurrentTime);
		string tmp2 = "Plane " + airplane1->getName() + " departs from airport " + CurrentAirport->getName();
		tmp += tmp2.c_str();
		tmp += "\r\n";
		results += tmp;

		Event* arrivalEvent;
		int newDestination = CurrentAirport->setDestinationIndex();


		CurrentAirport->setFlightTime(distanceMatrix[CurrentAirport->getIndex()][newDestination] / airplane1->getSpeed());

		arrivalEvent = new Event(CurrentAirport->m_flightTime + CurrentTime, CurrentAirport, event->PLANE_ARRIVES, AirportArray[newDestination]);
		arrivalEvent->setHandler(AirportArray[newDestination]);

		arrivalEvent->setPlaneInformation(airplane1);
		pq.push(arrivalEvent);


		if (CurrentAirport->EmergencyQueue.empty() == false) {
			Event* eEvent = CurrentAirport->EmergencyQueue.top();
			Event* elandedEvent = new Event(CurrentAirport->m_runwayTimeToLand + CurrentTime, CurrentAirport, event->PLANE_LANDED, eEvent->getPlaneDestination());
			elandedEvent->setPlaneInformation(eEvent->getPlaneInformation());
			pq.push(elandedEvent);
			CurrentAirport->setCirclingTime(CurrentTime - eEvent->getPlaneInformation()->getArrivalTime());
			CurrentAirport->EmergencyQueue.pop();
		}
		else {

			if (CurrentAirport->ArrivingQueue.empty() == true && CurrentAirport->TakingoffQueue.empty() == false) {
				Event* bEvent = CurrentAirport->TakingoffQueue.top();
				Event* departEvent = new Event(CurrentAirport->m_takeoffTime + CurrentTime, CurrentAirport, event->PLANE_DEPARTS, bEvent->getPlaneDestination());
				departEvent->setPlaneInformation(bEvent->getPlaneInformation());
				pq.push(departEvent);
				CurrentAirport->TakingoffQueue.pop();
			}
			else if (CurrentAirport->ArrivingQueue.empty() == false && CurrentAirport->TakingoffQueue.empty() == true) {
				Event* aEvent = CurrentAirport->ArrivingQueue.top();
				Event* landedEvent = new Event(CurrentAirport->m_runwayTimeToLand + CurrentTime, CurrentAirport, event->PLANE_LANDED, aEvent->getPlaneDestination());
				landedEvent->setPlaneInformation(aEvent->getPlaneInformation());
				pq.push(landedEvent);
				CurrentAirport->setCirclingTime(CurrentTime - aEvent->getPlaneInformation()->getArrivalTime());
				CurrentAirport->ArrivingQueue.pop();
			}
			else if (CurrentAirport->ArrivingQueue.empty() == true && CurrentAirport->TakingoffQueue.empty() == true) {
				CurrentAirport->freeRunway();
			}
			else {
				if (CurrentAirport->ArrivingQueue.top()->getTime() < CurrentAirport->TakingoffQueue.top()->getTime()) {
					Event* aEvent1 = CurrentAirport->ArrivingQueue.top();
					Event* landedEvent1 = new Event(CurrentAirport->m_runwayTimeToLand + CurrentTime, CurrentAirport, event->PLANE_LANDED, aEvent1->getPlaneDestination());
					landedEvent1->setPlaneInformation(aEvent1->getPlaneInformation());
					pq.push(landedEvent1);
					CurrentAirport->setCirclingTime(CurrentTime - aEvent1->getPlaneInformation()->getArrivalTime());
					CurrentAirport->ArrivingQueue.pop();
				}
				else {
					Event* bEvent1 = CurrentAirport->TakingoffQueue.top();
					Event* departEvent1 = new Event(CurrentAirport->m_takeoffTime + CurrentTime, CurrentAirport, event->PLANE_DEPARTS, bEvent1->getPlaneDestination());
					departEvent1->setPlaneInformation(bEvent1->getPlaneInformation());
					pq.push(departEvent1);
					CurrentAirport->TakingoffQueue.pop();

				}
			}
		}

		break;

	}
	}
}
