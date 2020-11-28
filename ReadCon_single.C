#ifdef __CLING__
R__LOAD_LIBRARY(libDelphes)
#include "classes/DelphesClasses.h"
#include "external/ExRootAnalysis/ExRootTreeReader.h"
#include "external/ExRootAnalysis/ExRootResult.h"
#else
class ExRootTreeReader;
class ExRootResult;
#endif


void cal_main(string inputfile)
{
    gSystem->Load("libDelphes");

    const char *c_inputfile = inputfile.c_str();
    TChain chain("Delphes");

    chain.Add(c_inputfile);

    // Create object of class ExRootTreeReader
    ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);
    Long64_t numberOfEntries = treeReader->GetEntries();

    // Get pointers to branches used in this analysis
    TClonesArray *branchJet = treeReader->UseBranch("Jet");
    TClonesArray *branchPhoton = treeReader->UseBranch("Photon");
    TClonesArray *branchParticle = treeReader->UseBranch("Particle");
    TClonesArray *branchEFlowTrack = treeReader->UseBranch("EFlowTrack");
    TClonesArray *branchEFlowPhoton = treeReader->UseBranch("EFlowPhoton");
    TClonesArray *branchEFlowNeutralHadron = treeReader->UseBranch("EFlowNeutralHadron");

    
    cout << "Event: " << 59 << endl;
    treeReader->ReadEntry(59);
    for (Long64_t jid = 0; jid < branchJet->GetEntriesFast(); ++jid)
    {
        int a = 0, b = 0, c = 0, d = 0;

        Jet *jet = (Jet *)branchJet->At(jid);

        cout << "\tJet ID: " << jid << endl;
        cout << "\t\t\t    \tEta \tPhi \tPT" << endl;

        for (Int_t i = 0; i < jet->Constituents.GetEntriesFast(); i++)
        {
            TObject *object = jet->Constituents.At(i);

            // Check if the constituent is accessible
            if (object == NULL)
            {
                a++;
                cout << "\t\t\t" << "NULL" << endl;
                continue;
            }
            else if (object->IsA() == Tower::Class())
            {
                Tower *tower = (Tower *)object;
                b++;
                cout << "\t\t\t" << object->ClassName() << ": "<< tower->Eta << " " << tower->Phi << " " << tower->ET << endl;
            }
            else if (object->IsA() == Track::Class())
            {
                Track *track = (Track *)object;
                c++;
                cout << "\t\t\t" << object->ClassName() << ": " << track->Eta << " " << track->Phi << " " << track->PT << endl;
            }
            else
            {
                GenParticle *particle = (GenParticle *)object;
                d++;
                cout << "\t\t\t" << object->ClassName() << ": " << particle->Eta << " " << particle->Phi << " " << particle->PT << endl;
            }
        }

        //cout << "\t\tConstit #: " << a << "," << b << "," << c << "," << d << endl;
    }
    

    
}

void ReadCon_single()
{
    cal_main("GGF_PU0_delphes_events.root");
}
