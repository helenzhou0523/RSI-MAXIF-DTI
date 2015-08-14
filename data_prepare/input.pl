#! /usr/bin/Env perl
use strict;
use Env;

my $home_path = "/cygdrive/c/Users/1/Desktop/学习/作业/RSI/research/database/";
my $read_path = $home_path."/testsample/";
my $out_path = $home_path."/testsample_result/";

opendir(TEMPFOLDER,"$read_path") or die "can't open the folder $read_path";

my @run_file = readdir(TEMPFOLDER);
# print join(" ",@run_file),"\n";

my $i;
my $filetestnum = 1000;
my $network = "/cygdrive/c/Users/1/Desktop/学习/作业/RSI/research/database/input_nomatrix_0.3";


for($i=0;$i<scalar(@run_file);$i++)
{
    next if(($run_file[$i] eq '.')or($run_file[$i] eq '..'));
    if($run_file[$i] =~ /random_DT(\d+)/)
    {
        if(($1>=0)&&($1<$filetestnum))
        {
            print $run_file[$i],"\n";
            my $temp_run = $read_path.$run_file[$i];
            my $temp_out = $out_path."maxif_result".$1.'.txt';
            system("a.exe $temp_run $network $temp_out");
#           `Maxflow.exe $temp_run $network $temp_out`;
            sleep(1);
        }
    }
}

close(TEMPFOLDER);
