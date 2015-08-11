#! /usr/bin/Env perl
use strict;
use Env;

my $home_path = "/data/home/szu/Lab/MAXIF";
my $read_path = $home_path."/RandomSample/";
my $out_path = $home_path."/RandomSample_Result/";

opendir(TEMPFOLDER,"$read_path") or die "can't open the folder $read_path";

my @run_file = readdir(TEMPFOLDER);
# print join(" ",@run_file),"\n";

my $i;
my $filetestnum = 100;
my $network = "DrugTargetNetwork.txt";


for($i=0;$i<scalar(@run_file);$i++)
{
    next if(($run_file[$i] eq '.')or($run_file[$i] eq '..'));
    if($run_file[$i] =~ /testsample(\d+)/)
    {
        if(($1>0)&&($1<=$filetestnum))
        {
            print $run_file[$i],"\n";
            my $temp_run = $read_path.$run_file[$i];
            my $temp_out = $out_path."Resulttestsample".$1.'.txt';
            system(./Maxflow $temp_run $network $temp_out);
            sleep(1);
        }
    }
}

close(TEMPFOLDER);
