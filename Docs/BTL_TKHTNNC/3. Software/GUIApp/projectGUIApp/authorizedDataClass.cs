using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace projectGUIApp
{
    class authorizedDataClass
    {
        public string Name { get; set; }
        public string ID { get; set; }

        public string InOrOut { get; set; }

        public string AuthorizeAtTime { get; set; }

        public authorizedDataClass(string name, string id, string inOrOut, string authorizeAtTime)
        {
            this.Name = name;
            this.ID = id;
            this.InOrOut = inOrOut;
            this.AuthorizeAtTime = authorizeAtTime;
        }

        // Save authorized info (the present and the past)
        public static List<authorizedDataClass> ListAuthorizedData = new List<authorizedDataClass>();
    }
}
